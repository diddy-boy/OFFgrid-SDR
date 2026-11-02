# pl_mpeg in OFFgrid-SDR

OFFgrid-SDR plays classic DAB stations (MPEG-1 Audio Layer II, "MP2") with the MP2 decoder of **pl_mpeg** by
Dominic Szablewski, built for WebAssembly and embedded in `index.html` (the `mp2wasm` block). pl_mpeg's MP2
decoder is derived from kjmp2 by Martin J. Fiedler.

- **Project:** https://github.com/phoboslab/pl_mpeg
- **Version:** commit `c871f2be022ece7ef4f64230b4fb8e1fb9eb6023`
- **Licence:** MIT: see the notice at the top of `pl_mpeg.h`, and `licenses/pl_mpeg-LICENSE.txt`. OFFgrid-SDR as a
  whole is under the GNU GPL, version 3 or later, with which the MIT licence is compatible.

## What's here

| File | What it is |
|---|---|
| `pl_mpeg.h` | pl_mpeg, exactly as published at that commit (a single file: the decoders and their source) |
| `mp2_glue.c` | OFFgrid-SDR's small wrapper (`mp2_open`, `mp2_decode`, `mp2_rate`): one whole MP2 frame in, 1152 stereo samples out. GPL-3.0-or-later |
| `build.sh` | rebuilds `mp2.wasm` exactly as embedded |

pl_mpeg is used unchanged. Only its audio decoder is in the build: the linker leaves out everything the wrapper
doesn't use, including the video decoder.

## Rebuilding

    sh build.sh

The result, `mp2.wasm`, should have the SHA-256 `3bc29a2763adf00a7a55de542627613f6942b98b8a63b1062d79f09ede6889ed` (25,035 bytes), identical to the build in `index.html`.
