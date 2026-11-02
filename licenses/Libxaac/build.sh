#!/bin/sh
# Rebuilds xaac.wasm, OFFgrid-SDR's xHE-AAC decoder (libxaac, commit 2fbadd5, with OFFgrid-SDR's wrapper), exactly as
# embedded in index.html (the "xaacwasm" block, gzip-compressed, in base64).
# Needs: clang-18 and wasm-ld-18 (LLVM 18), wasi-libc, and libclang_rt.builtins for wasm32. On Ubuntu 24.04:
#   apt install clang-18 lld-18 wasi-libc libclang-rt-18-dev-wasm32
# Run in this folder:  sh build.sh       Result: xaac.wasm, and its SHA-256, which should be
#   d98457a2b66fbeb27776119742b6301aa496e8d4b0d52f758379f1b5b3be04b0 (1,302,669 bytes)
set -e
export LC_ALL=C
H=$(pwd); O=$H/build/obj
rm -rf build && mkdir -p $O && tar -xzf libxaac-2fbadd5-decoder-source.tar.gz -C build
W="--target=wasm32-wasi -I$H/wasi-include -isystem /usr/include/wasm32-wasi"
I="-Idecoder -Idecoder/drc_src -Icommon -Iinclude"
# (compiled from inside the source folder, with these relative paths: two of libxaac's files embed their own path
#  in assertion messages, so the paths must match for an identical build)
cd build/libxaac-2fbadd5
# the decoder files libxaac's own build lists (decoder_sources.txt), its loudness control and common code
while read f; do clang-18 $W -Oz $I -w -c ./$f -o $O/__$(echo $f | tr '/.' '__').o; done < $H/decoder_sources.txt
for f in decoder/drc_src/*.c common/*.c; do clang-18 $W -Oz $I -w -c $f -o $O/$(echo $f | tr '/.' '__').o; done
# as libxaac's own x86 build: its x86 function selector (plain C) and the generic QMF file
clang-18 $W -Oz $I -w -c decoder/x86/ixheaacd_function_selector_x86.c -o $O/sel_x86.o
clang-18 $W -Oz $I -w -c decoder/generic/ixheaacd_qmf_dec_generic.c -o $O/qmf_generic.o
# OFFgrid-SDR's wrapper
clang-18 $W -Oz $I -w -c $H/xaac_glue.c -o $O/xaac_glue.o
cd $H
wasm-ld-18 --no-entry --gc-sections --strip-all -z stack-size=1048576 \
  --export=xaac_open --export=xaac_decode --export=xaac_close --export=xaac_rate --export=xaac_channels \
  --export=malloc --export=free -L/usr/lib/wasm32-wasi $O/*.o -lc -lm \
  /usr/lib/llvm-18/lib/clang/18/lib/wasi/libclang_rt.builtins-wasm32.a -o xaac.wasm
sha256sum xaac.wasm
