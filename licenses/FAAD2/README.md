# FAAD2 in OFFgrid-SDR: the source and how it's built

OFFgrid-SDR plays the sound of DRM digital radio with **[FAAD2](https://github.com/knik0/faad2)**, the open-source AAC
decoder, built with its DRM support and compiled to WebAssembly. That compiled build is embedded in `index.html`, in the
`<script type="text/plain" id="faadwasm">` block (the WebAssembly file, compressed with `gzip -9`, then base64).

FAAD2 is licensed under the **GNU General Public License, version 2 or (at your option) any later version**, and
OFFgrid-SDR, which is GPL-3.0-or-later, includes it under version 3. The GPL asks that anyone who receives a compiled
program can also get its exact source and see how it was built. This folder provides both.

## What's here

| File | What it is |
|---|---|
| `faad2-a335040-source.tar.gz` | FAAD2's complete source, **unmodified**, at commit `a335040022e14ff9b6c54bbd459590d4c7edffe8` (23 October 2026), exactly as used |
| `build.sh` | The exact commands that build the WebAssembly file from that source |
| `README.md` | This file |

FAAD2's licence text is beside this folder, in `licenses/faad2-COPYING.txt`.

## OFFgrid-SDR's change to FAAD2 (from version 2.1)

FAAD2 is built with **one change**, in `libfaad/syntax.c`, published here as `faad2-dabplus-fill-elements.diff`
and applied by `build.sh`. Each changed place is marked "OFFgrid-SDR" in the source.

- **Why:** OFFgrid-SDR's FAAD2 is built with DRM support (`DRM_SUPPORT`), and also decodes **DAB+**. In a
  DRM-enabled build, FAAD2 refuses *every* AAC fill element that isn't SBR data (error 30, "No standard extension
  payload allowed in DRM"), whatever the stream. DRM forbids them, but DAB+ encoders use them routinely (padding,
  loudness information), so a DRM-enabled build threw away half of a real DAB+ station's audio frames.
- **The change:** the refusal now applies only to DRM streams (object type `DRM_ER_LC`); other streams' fill
  elements are parsed as in a standard build. The three functions that parse them (`extension_payload`,
  `dynamic_range_info`, `excluded_channels`) are compiled in DRM-enabled builds too.
- **Checked:** BBC Radio 1 Dance (DAB+, HE-AAC v2) received off air decodes exactly as a FAAD2 built without DRM
  support decodes it; and every DRM recording OFFgrid-SDR is tested on decodes exactly as before.
- `build.sh` also exports `NeAACDecInit2`, which DAB+ uses to configure the decoder.

## What OFFgrid-SDR changes

Nothing in FAAD2's source. The build only chooses settings:

- `-DDRM_SUPPORT`: FAAD2's own option for DRM (960-sample frames, DRM's error-resilient layout, its SBR and parametric stereo).
- `-Oz`: optimised for size.
- A 1 MB stack (`-z stack-size=1048576`): WebAssembly's default 64 kB overflows in FAAD2's parametric stereo decoding.
- Only the functions OFFgrid-SDR calls are kept: `NeAACDecOpen`, `NeAACDecInitDRM`, `NeAACDecDecode`, `NeAACDecClose`,
  `NeAACDecGetErrorMessage`, plus `malloc` and `free`.

## Rebuilding it

On Ubuntu 24.04 (other systems with the same tools work too):

```sh
sudo apt-get install clang-18 lld-18 wasi-libc libclang-rt-18-dev-wasm32
sh build.sh
```

The result, `faad_drm.wasm`, should be **248,181 bytes** with SHA-256

```
1e54e377563c4f316306b4498c5b607c18efe21c72767b1135c3a206f818a7e5
```

That is byte-for-byte the build embedded in OFFgrid-SDR 2.0 (checked by rebuilding from this folder alone).
To put a build into `index.html`, replace the contents of the `faadwasm` block with the output of:

```sh
gzip -9 -c faad_drm.wasm | base64 -w0
```

## Credits

FAAD2: Copyright (C) 2003-2005 M. Bakker, Nero AG; Copyright 2002-2004 Ahead Software AG; and the FAAD2 contributors.
Maintained at [github.com/knik0/faad2](https://github.com/knik0/faad2).
