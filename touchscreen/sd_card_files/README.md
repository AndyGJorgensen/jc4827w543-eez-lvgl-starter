# Files for the board's micro SD card

Copy the files in this folder to the **root** of a FAT32-formatted micro SD card, then insert it
in the board's TF slot.

| File | Used by |
|---|---|
| `test.wav` | Settings screen, **Test Sound** button (`TEST_SOUND_PATH` in `include/app_config.h`) |

Sounds must be WAV, 16-bit PCM, mono or stereo, any sample rate (22050 or 44100 Hz are typical).
Volume: `AUDIO_VOLUME_PERCENT` in `include/app_config.h`.
