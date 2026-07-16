#!/bin/bash
set -e

EMSDK_VERSION="3.1.73"

if [ ! -d "emsdk" ]; then
    echo "Downloading Emscripten SDK..."
    git clone https://github.com/emscripten-core/emsdk.git
    cd emsdk
    ./emsdk install $EMSDK_VERSION
    ./emsdk activate $EMSDK_VERSION
    cd ..
fi

source ./emsdk/emsdk_env.sh

echo "Building libKeyFinder WASM..."

# Configure
emcmake cmake -B build     -DCMAKE_BUILD_TYPE=Release     -DFFTW3_ROOT=$(pwd)/emsdk/upstream/emscripten/cache/sysroot

# Build
emmake make -C build -j$(nproc)

echo "Linking WASM module..."

# Link into WASM
emcc -O3 \
    -s WASM=1 \
    -s EXPORTED_FUNCTIONS='["_malloc","_free","_keyfinder_create","_keyfinder_destroy","_keyfinder_detect_key"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap","getValue","setValue","UTF8ToString","stringToUTF8"]' \
    -s MODULARIZE=1 \
    -s EXPORT_NAME='createKeyFinderModule' \
    -s ENVIRONMENT='web,worker' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s INITIAL_MEMORY=67108864 \
    -s FILESYSTEM=0 \
    -o dist/libkeyfinder-core.js \
    build/libkeyfinder-core.a \
    $(find emsdk/upstream/emitter/ -name "libfftw3.a" 2>/dev/null || echo "")

echo ""
echo "=== Build complete ==="
echo "Output: dist/libkeyfinder-core.wasm"
echo "Output: dist/libkeyfinder-core.js"
ls -lh dist/
