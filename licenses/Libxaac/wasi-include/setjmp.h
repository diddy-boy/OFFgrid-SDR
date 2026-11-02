/* Part of OFFgrid-SDR. SPDX-License-Identifier: GPL-3.0-or-later
   WASI's C library has no setjmp/longjmp: this stands in for it when building libxaac for WebAssembly.
   setjmp returns 0 (the normal path); longjmp, which libxaac uses only on damaged audio data, stops the module with
   a trap: OFFgrid-SDR catches it, makes a fresh instance and reopens the decoder. */
#ifndef XAAC_SETJMP_STUB
#define XAAC_SETJMP_STUB
typedef long jmp_buf[8];
#define setjmp(env) 0
static inline void longjmp(jmp_buf env, int v) { (void)env; (void)v; __builtin_trap(); }
#endif
