# libxaac in OFFgrid-SDR

OFFgrid-SDR plays DRM stations broadcasting in **xHE-AAC** with **libxaac**, the xHE-AAC decoder by Ittiam Systems,
part of the Android Open Source Project, built for WebAssembly and embedded in `index.html` (the `xaacwasm` block).

- **Project:** https://github.com/ittiam-systems/libxaac
- **Version:** commit `2fbadd57bca46693b7a077bcf1513131106d960c` (1 October 2026)
- **Licence:** Apache License 2.0: see `LICENSE` and `NOTICE` inside the source archive, and
  `libxaac-LICENSE.txt` and `libxaac-NOTICE.txt`, beside this folder in `licenses`. OFFgrid-SDR as a whole is under the GNU GPL,
  version 3 or later, with which the Apache License 2.0 is compatible.

## What's here

| File | What it is |
|---|---|
| `libxaac-2fbadd5-decoder-source.tar.gz` | libxaac's decoder source at that commit, exactly as published (decoder, common code, licence files) |
| `decoder_sources.txt` | the decoder files libxaac's own build lists, in its order |
| `xaac_glue.c` | OFFgrid-SDR's small wrapper around libxaac's API (`xaac_open`, `xaac_decode`, `xaac_close`); GPL-3.0-or-later |
| `wasi-include/setjmp.h` | a stand-in for `setjmp.h`, which WebAssembly's C library lacks (see below) |
| `build.sh` | rebuilds `xaac.wasm` exactly as embedded |
| `demo-jingle/` | how the demo's xHE-AAC jingle was encoded (not part of OFFgrid-SDR itself) |

## No libxaac file is changed

The build uses libxaac's files exactly as published. It differs from libxaac's own PC build only in these ways:

1. **`setjmp.h`:** libxaac jumps out of damaged audio data with `setjmp`/`longjmp`, which WebAssembly's C library
   (WASI) doesn't provide. The stand-in makes `setjmp` return 0, the normal path, and `longjmp` stop the module with a
   WebAssembly trap; OFFgrid-SDR catches the trap, makes a fresh instance of the module and reopens the decoder, so a
   damaged frame costs a moment of sound, as on any receiver.
2. **The function selector:** libxaac's own x86 build uses `decoder/x86/ixheaacd_function_selector_x86.c` (plain C)
   with `decoder/generic/ixheaacd_qmf_dec_generic.c`; this build does the same. (Its generic selector,
   `ixheaacd_function_selector_generic.c`, no longer matches the current function signatures.)
3. **The wrapper**, `xaac_glue.c`, OFFgrid-SDR's own code, following libxaac's test program in its raw mode: the
   decoder configuration first, then one whole audio frame at a time.

OFFgrid-SDR translates DRM's compact xHE-AAC configuration (from the SDC) into the standard MPEG-4
AudioSpecificConfig that libxaac reads, following Fraunhofer FDK's DRM parser; that code is in `index.html`.

## Rebuilding

    sh build.sh

The result, `xaac.wasm`, should have the SHA-256
`d98457a2b66fbeb27776119742b6301aa496e8d4b0d52f758379f1b5b3be04b0` (1,302,669 bytes), identical to the
build in `index.html`. `build.sh` lists the tools needed.
