/* SPDX-License-Identifier: GPL-3.0-or-later
   Part of OFFgrid-SDR (https://github.com/diddy-boy/OFFgrid-SDR): a small wrapper around pl_mpeg's MP2 (MPEG-1 Audio
   Layer II) decoder, for classic DAB. One whole MP2 frame in, 1152 stereo samples out (interleaved floats). */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define PL_MPEG_IMPLEMENTATION
#include "pl_mpeg.h"
static plm_buffer_t *buf = NULL;
static plm_audio_t *aud = NULL;
int mp2_open(void) {
  if (aud) plm_audio_destroy(aud);
  buf = plm_buffer_create_for_appending(16384); if (!buf) return 0;
  aud = plm_audio_create_with_buffer(buf, 1); return aud != NULL;
}
/* returns the number of samples per channel written to out (stereo, interleaved), or 0 */
int mp2_decode(const unsigned char *frame, int len, float *out) {
  if (!aud) return 0;
  plm_buffer_write(buf, (uint8_t *)frame, (size_t)len);
  plm_samples_t *s = plm_audio_decode(aud); if (!s) return 0;
  memcpy(out, s->interleaved, sizeof(float) * 2 * s->count); return s->count;
}
int mp2_rate(void) { return aud ? plm_audio_get_samplerate(aud) : 0; }
