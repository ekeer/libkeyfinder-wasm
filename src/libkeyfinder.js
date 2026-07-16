/**
 * libKeyFinder WASM wrapper for browser
 *
 * Usage:
 *   import initKeyFinder from './libkeyfinder.js';
 *   const kf = await initKeyFinder();
 *   const key = kf.detectKey(float32Array, sampleRate);
 *   // key => "Em", "C", "Am", etc.
 */

let moduleInstance = null;

export default async function initKeyFinder(wasmUrl) {
  if (moduleInstance) return moduleInstance;

  const createModule = (await import('./libkeyfinder-core.js')).default;

  const wasm = await createModule({
    locateFile: (path) => {
      if (path.endsWith('.wasm')) {
        return wasmUrl || path;
      }
      return path;
    },
  });

  const api = {
    _handle: null,

    async detectKey(samples, sampleRate) {
      if (!this._handle) {
        this._handle = wasm._keyfinder_create();
      }

      const ptr = wasm._malloc(samples.length * 4);
      wasm.HEAPF32.set(samples, ptr >> 2);

      const resultPtr = wasm._keyfinder_detect_key(
        this._handle,
        ptr,
        samples.length,
        sampleRate
      );

      wasm._free(ptr);

      if (!resultPtr) return null;
      return wasm.UTF8ToString(resultPtr);
    },

    destroy() {
      if (this._handle) {
        wasm._keyfinder_destroy(this._handle);
        this._handle = null;
      }
    },
  };

  moduleInstance = api;
  return api;
}
