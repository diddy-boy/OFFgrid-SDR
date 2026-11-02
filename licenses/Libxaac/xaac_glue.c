/* SPDX-License-Identifier: GPL-3.0-or-later
   Part of OFFgrid-SDR (https://github.com/diddy-boy/OFFgrid-SDR).

   OFFgrid-SDR: a small wrapper around libxaac's decoder API for DRM xHE-AAC, following libxaac's own test program
   (test/decoder/ixheaacd_main.c) in its raw mode: the first input is the AudioSpecificConfig, each later input is
   one whole audio frame. Output: 16-bit PCM, interleaved. */
#include <stdlib.h>
#include <string.h>
#include "ixheaac_type_def.h"
#include "ixheaac_error_standards.h"
#include "ixheaacd_apicmd_standards.h"
#include "ixheaacd_memory_standards.h"
#include "ixheaacd_aac_config.h"

extern IA_ERRORCODE ixheaacd_dec_api(pVOID p_ia_module_obj, WORD32 i_cmd, WORD32 i_idx, pVOID pv_value);

typedef struct { void *api; UWORD8 *in; WORD32 in_size; WORD16 *out; void *mem[64]; WORD32 nmem; WORD32 init_done, rate, ch; } XAAC;

static void *alloc_aligned(XAAC *x, WORD32 size, WORD32 align) {
  if (align < 4) align = 4; char *m = (char *)calloc(1, size + align); if (!m || x->nmem >= 64) return NULL;
  x->mem[x->nmem++] = m; return m + (align - ((size_t)m % align)) % align;
}
void xaac_close(XAAC *x) { if (!x) return; for (int i = 0; i < x->nmem; i++) free(x->mem[i]); free(x); }

XAAC *xaac_open(const UWORD8 *asc, WORD32 asc_len) {
  XAAC *x = (XAAC *)calloc(1, sizeof(XAAC)); UWORD32 sz = 0; WORD32 n = 0, v;
  ixheaacd_dec_api(NULL, IA_API_CMD_GET_API_SIZE, 0, &sz);
  if (!(x->api = alloc_aligned(x, sz, 4))) goto fail;
  if (ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_API_PRE_CONFIG_PARAMS, NULL) & IA_FATAL_ERROR) goto fail;
  v = 16; ixheaacd_dec_api(x->api, IA_API_CMD_SET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_PCM_WDSZ, &v);
  v = 1;  ixheaacd_dec_api(x->api, IA_API_CMD_SET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_MP4FLAG, &v);
  ixheaacd_dec_api(x->api, IA_API_CMD_GET_MEMTABS_SIZE, 0, &sz);
  { void *t = alloc_aligned(x, sz, 4); if (!t) goto fail; ixheaacd_dec_api(x->api, IA_API_CMD_SET_MEMTABS_PTR, 0, t); }
  if (ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_API_POST_CONFIG_PARAMS, NULL) & IA_FATAL_ERROR) goto fail;
  ixheaacd_dec_api(x->api, IA_API_CMD_GET_N_MEMTABS, 0, &n);
  for (WORD32 i = 0; i < n; i++) { WORD32 s = 0, a = 0, ty = 0; void *p;
    ixheaacd_dec_api(x->api, IA_API_CMD_GET_MEM_INFO_SIZE, i, &s); ixheaacd_dec_api(x->api, IA_API_CMD_GET_MEM_INFO_ALIGNMENT, i, &a);
    ixheaacd_dec_api(x->api, IA_API_CMD_GET_MEM_INFO_TYPE, i, &ty);
    if (!(p = alloc_aligned(x, s, a))) goto fail; ixheaacd_dec_api(x->api, IA_API_CMD_SET_MEM_PTR, i, p);
    if (ty == IA_MEMTYPE_INPUT) { x->in = (UWORD8 *)p; x->in_size = s; } if (ty == IA_MEMTYPE_OUTPUT) x->out = (WORD16 *)p; }
  if (!x->in || !x->out || asc_len > x->in_size) goto fail;
  /* initialise with the configuration */
  memcpy(x->in, asc, asc_len); v = asc_len; ixheaacd_dec_api(x->api, IA_API_CMD_SET_INPUT_BYTES, 0, &v);
  if (ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_PROCESS, NULL) & IA_FATAL_ERROR) goto fail;
  ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_DONE_QUERY, &x->init_done);
  if (x->init_done) { ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_SAMP_FREQ, &x->rate);
    ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_NUM_CHANNELS, &x->ch); }
  return x;
fail: xaac_close(x); return NULL;
}
/* one frame in; returns the number of 16-bit samples written to *pcm (all channels), 0 for none, or < 0 for an error */
WORD32 xaac_decode(XAAC *x, const UWORD8 *frame, WORD32 len, WORD16 **pcm) {
  WORD32 v = len, done = 0, outb = 0; IA_ERRORCODE e; *pcm = x->out;
  if (len > x->in_size) return -1;
  memcpy(x->in, frame, len); ixheaacd_dec_api(x->api, IA_API_CMD_SET_INPUT_BYTES, 0, &v);
  if (!x->init_done) {
    e = ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_PROCESS, NULL); if (e & IA_FATAL_ERROR) return -2;
    ixheaacd_dec_api(x->api, IA_API_CMD_INIT, IA_CMD_TYPE_INIT_DONE_QUERY, &x->init_done);
    if (x->init_done) { ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_SAMP_FREQ, &x->rate);
      ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_NUM_CHANNELS, &x->ch); }
    return 0;
  }
  e = ixheaacd_dec_api(x->api, IA_API_CMD_EXECUTE, IA_CMD_TYPE_DO_EXECUTE, NULL); if (e & IA_FATAL_ERROR) return -3;
  ixheaacd_dec_api(x->api, IA_API_CMD_EXECUTE, IA_CMD_TYPE_DONE_QUERY, &done);
  ixheaacd_dec_api(x->api, IA_API_CMD_GET_OUTPUT_BYTES, 0, &outb);
  ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_SAMP_FREQ, &x->rate);
  ixheaacd_dec_api(x->api, IA_API_CMD_GET_CONFIG_PARAM, IA_XHEAAC_DEC_CONFIG_PARAM_NUM_CHANNELS, &x->ch);
  return (e & 0x7fffffff) && !outb ? -4 : outb / 2;
}
WORD32 xaac_rate(XAAC *x) { return x->rate; }
WORD32 xaac_channels(XAAC *x) { return x->ch; }
