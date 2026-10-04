#include "audio.h"

#include <Arduino.h>
#include <SD.h>
#include <driver/i2s.h>

#include "app_config.h"
#include "board_pins.h"
#include "eez_vars.h"
#include "sd_card.h"
#include "status_text.h"
#include "ui/actions.h"

#define I2S_PORT       I2S_NUM_0
#define READ_FRAMES    256           // stereo frames per SD read / I2S write

static volatile bool playing = false;
static StatusText<40> status("Audio: idle");
static File wav_file;

struct wav_info_t
{
  uint32_t sample_rate;
  uint16_t channels;
  uint32_t data_bytes;
};

// Parse RIFF/WAVE chunks; leaves the file positioned at the start of the sample data
static bool read_wav_header(File &f, wav_info_t &info)
{
  uint8_t hdr[12];
  if (f.read(hdr, 12) != 12 || memcmp(hdr, "RIFF", 4) || memcmp(hdr + 8, "WAVE", 4))
    return false;

  bool have_fmt = false;
  uint8_t chunk[8];
  while (f.read(chunk, 8) == 8)
  {
    uint32_t size = chunk[4] | chunk[5] << 8 | chunk[6] << 16 | (uint32_t)chunk[7] << 24;
    if (!memcmp(chunk, "fmt ", 4))
    {
      uint8_t fmt[16];
      if (size < 16 || f.read(fmt, 16) != 16)
        return false;
      uint16_t format = fmt[0] | fmt[1] << 8;
      info.channels = fmt[2] | fmt[3] << 8;
      info.sample_rate = fmt[4] | fmt[5] << 8 | fmt[6] << 16 | (uint32_t)fmt[7] << 24;
      uint16_t bits = fmt[14] | fmt[15] << 8;
      if (format != 1 || bits != 16 || info.channels < 1 || info.channels > 2)
        return false; // only 16-bit PCM mono/stereo
      f.seek(f.position() + size - 16 + (size & 1));
      have_fmt = true;
    }
    else if (!memcmp(chunk, "data", 4))
    {
      info.data_bytes = size;
      return have_fmt;
    }
    else
      f.seek(f.position() + size + (size & 1));
  }
  return false;
}

static void play_task(void *arg)
{
  wav_info_t info = *(wav_info_t *)arg;
  delete (wav_info_t *)arg;

  i2s_set_clk(I2S_PORT, info.sample_rate, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_STEREO);

  static int16_t in[READ_FRAMES * 2];
  static int16_t out[READ_FRAMES * 2];
  const int32_t gain = AUDIO_VOLUME_PERCENT * 256 / 100;
  const size_t frame_in = 2 * info.channels;
  uint32_t left = info.data_bytes;

  while (left > 0)
  {
    size_t want = min((uint32_t)(READ_FRAMES * frame_in), left);
    int got = wav_file.read((uint8_t *)in, want);
    if (got <= 0)
      break;
    left -= got;

    int frames = got / frame_in;
    for (int i = 0; i < frames; i++)
    {
      int16_t l = info.channels == 2 ? in[2 * i] : in[i];
      int16_t r = info.channels == 2 ? in[2 * i + 1] : in[i];
      out[2 * i] = (int16_t)((l * gain) >> 8);
      out[2 * i + 1] = (int16_t)((r * gain) >> 8);
    }
    size_t written;
    i2s_write(I2S_PORT, out, frames * 4, &written, portMAX_DELAY);
  }

  wav_file.close();
  i2s_zero_dma_buffer(I2S_PORT); // silence instead of repeating the last buffer
  status.set("Audio: done");
  playing = false;
  vTaskDelete(nullptr);
}

void audio_init()
{
  i2s_config_t cfg = {};
  cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
  cfg.sample_rate = 44100;
  cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
  cfg.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
  cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
  cfg.dma_buf_count = 8;
  cfg.dma_buf_len = 256;
  cfg.tx_desc_auto_clear = true; // output silence on underrun

  i2s_pin_config_t pins = {};
  pins.mck_io_num = I2S_PIN_NO_CHANGE;
  pins.bck_io_num = I2S_BCLK;
  pins.ws_io_num = I2S_LRCLK;
  pins.data_out_num = I2S_DOUT;
  pins.data_in_num = I2S_PIN_NO_CHANGE;

  if (i2s_driver_install(I2S_PORT, &cfg, 0, nullptr) != ESP_OK || i2s_set_pin(I2S_PORT, &pins) != ESP_OK)
  {
    status.set("Audio: I2S init failed");
    return;
  }
  i2s_zero_dma_buffer(I2S_PORT);
}

bool audio_play_wav(const char *path)
{
  if (playing)
    return false;
  if (!sd_card_ready())
  {
    status.set("Audio: no SD card");
    return false;
  }

  wav_file = SD.open(path);
  if (!wav_file)
  {
    status.set("Audio: %s not found", path);
    return false;
  }

  wav_info_t *info = new wav_info_t();
  if (!read_wav_header(wav_file, *info))
  {
    wav_file.close();
    delete info;
    status.set("Audio: not a 16-bit PCM WAV");
    return false;
  }

  status.set("Audio: playing %s", path);
  playing = true;
  xTaskCreate(play_task, "audio", 4096, info, 2, nullptr);
  return true;
}

/*------------------------------------------------------------------------------
 * EEZ native action / variables
 *----------------------------------------------------------------------------*/
extern "C" void action_play_test_sound(lv_event_t *e)
{
  audio_play_wav(TEST_SOUND_PATH);
}

EEZ_VAR_STRING_RO(audio_status, status.c_str())
