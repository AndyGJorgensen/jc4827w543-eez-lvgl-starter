/*******************************************************************************
 * Speaker: I2S amp (NS4168) on the "Speak" connector, WAV playback from SD
 *
 * Implements the EEZ native action play_test_sound and native variable
 * audio_status. Playback runs in its own task so the UI keeps running.
 ******************************************************************************/
#pragma once

#include <stdbool.h>

// Install the I2S driver
void audio_init();

// Play a 16-bit PCM WAV file from the SD card in the background; false if busy/not found
bool audio_play_wav(const char *path);
