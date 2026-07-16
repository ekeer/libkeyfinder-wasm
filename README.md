# libKeyFinder WASM

[libKeyFinder](https://github.com/mixxxdj/libkeyfinder) compiled to WebAssembly for browser-based musical key detection.

## Usage

```js
import initKeyFinder from './libkeyfinder-core.js';

const kf = await initKeyFinder();

// Decode audio
const audioCtx = new OfflineAudioContext(1, 1, 44100);
const audioBuffer = await audioCtx.decodeAudioData(wavArrayBuffer);

// Run key detection
const result = kf.detectKey(audioBuffer.getChannelData(0), audioBuffer.sampleRate);
console.log(result.key);   // "Em", "C", "Am", etc.
console.log(result.bpm);   // 120
```

## Build from source

```bash
git clone --recurse-submodules https://github.com/ekeer/libkeyfinder-wasm.git
cd libkeyfinder-wasm
./build.sh
```

The build script uses [Emscripten](https://emscripten.org/) via Docker.

## Releases

Pre-built WASM files are available in [Releases](https://github.com/ekeer/libkeyfinder-wasm/releases).
