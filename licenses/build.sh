#!/bin/sh
# Builds faad_drm.wasm: FAAD2 (unmodified, commit a335040) with its DRM support, as WebAssembly, exactly as embedded in
# OFFgrid-SDR's index.html (the "faadwasm" block: this file, gzip -9, base64).
#
# Needs (Ubuntu 24.04 packages): clang-18 lld-18 wasi-libc libclang-rt-18-dev-wasm32
#   sudo apt-get install clang-18 lld-18 wasi-libc libclang-rt-18-dev-wasm32
# Run in this folder:  sh build.sh
# The result should have SHA-256 3f6cf1795dd2a6035d28c0829b8ebd0683293da140a3e1f95bc92cfe49f451b7 (245,487 bytes).
set -e
rm -rf faad2-a335040 obj && tar xzf faad2-a335040-source.tar.gz && mkdir obj
cd faad2-a335040
W="--target=wasm32-wasi -isystem /usr/include/wasm32-wasi"
D="-DHAVE_INTTYPES_H=1 -DHAVE_MEMCPY=1 -DHAVE_STRING_H=1 -DHAVE_STRINGS_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_LRINTF=1 -DPACKAGE_VERSION=\"2.11-wasm\" -DAPPLY_DRC -DDRM_SUPPORT"
for f in libfaad/*.c; do
  clang-18 $W -Oz $D -Iinclude -Ilibfaad -c "$f" -o ../obj/$(basename "$f" .c).o
done
cd ..
wasm-ld-18 --no-entry --gc-sections --strip-all \
  --export=NeAACDecOpen --export=NeAACDecInitDRM --export=NeAACDecDecode --export=NeAACDecClose --export=NeAACDecGetErrorMessage \
  --export=malloc --export=free \
  -L/usr/lib/wasm32-wasi obj/*.o -lc -lm /usr/lib/llvm-18/lib/clang/18/lib/wasi/libclang_rt.builtins-wasm32.a \
  -o faad_drm.wasm
sha256sum faad_drm.wasm
echo "For index.html's \"faadwasm\" block:  gzip -9 -c faad_drm.wasm | base64 -w0"
