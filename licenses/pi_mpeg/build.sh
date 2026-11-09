#!/bin/sh
# Rebuilds mp2.wasm, OFFgrid-SDR's MP2 decoder for classic DAB (pl_mpeg, with OFFgrid-SDR's wrapper), exactly as
# embedded in index.html (the "mp2wasm" block, gzip-compressed, in base64).
# Needs: clang-18 and wasm-ld-18 (LLVM 18), wasi-libc, libclang_rt.builtins for wasm32. On Ubuntu 24.04:
#   apt install clang-18 lld-18 wasi-libc libclang-rt-18-dev-wasm32
# Run in this folder:  sh build.sh       Result: mp2.wasm, and its SHA-256, which should be
#   7dc975ba49cb94dc6a96e683447ae264ce9371b8c441812fce91465c0953a664 (25,100 bytes)
set -e
W="--target=wasm32-wasi -isystem /usr/include/wasm32-wasi"
clang-18 $W -Oz -w -c mp2_glue.c -o mp2_glue.o
wasm-ld-18 --no-entry --gc-sections --strip-all --export=mp2_open --export=mp2_decode --export=mp2_rate \
  --export=malloc --export=free -L/usr/lib/wasm32-wasi mp2_glue.o -lc -lm \
  /usr/lib/llvm-18/lib/clang/18/lib/wasi/libclang_rt.builtins-wasm32.a -o mp2.wasm
sha256sum mp2.wasm
