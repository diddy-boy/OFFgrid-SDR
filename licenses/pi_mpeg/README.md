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

The result, `mp2.wasm`, should have the SHA-256 `7dc975ba49cb94dc6a96e683447ae264ce9371b8c441812fce91465c0953a664` (25,100 bytes), identical to the build in `index.html`.


## Changes for OFFgrid-SDR 2.2

Three small changes, so that every kind of DAB MP2 station plays (found by testing every combination the DAB standard
allows, and by a real broadcast: Times Radio, Fix Radio and Premier on the UK's Sound Digital multiplex were silent).
They are in `pl_mpeg-dab-changes.diff`, against the original `pl_mpeg.h` of the commit above, and marked
"OFFgrid-SDR" in the source:

1. **MPEG-2's half sample rates** (16, 22.05 and 24 kHz), which DAB uses for many speech stations: the header check
   now accepts MPEG-2 Layer II as well as MPEG-1, using the MPEG-2 halves of the bit-rate and sample-rate tables and the
   MPEG-2 allocation table (ISO 13818-3 B.1), as kjmp2 1.1 does. (pl_mpeg already contained these tables.)
2. **The frame sync search** recognises MPEG-2 Layer II headers (`0xF4`/`0xF5`) as well as MPEG-1's (`0xFC`/`0xFD`), as
   kjmp2 1.1 does: DAB frames end with PAD bytes, so the decoder searches for the next header after each frame.
3. **Stereo, joint stereo and dual channel** are treated alike when checking that a frame's header matches the last
   one's: encoders switch frames between joint and plain stereo as the audio needs, and every frame after the first
   was being thrown away. A change between mono and two channels still counts as a false sync.

Checked against ffmpeg's decoding of the same frames: 51 combinations (48 kHz at 32-384 kbit/s and 24 kHz at 8-160
kbit/s, in mono, stereo, joint stereo and dual channel) all match, and real 24 and 48 kHz broadcasts at 0.99-0.9996.
