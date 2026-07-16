#include <emscripten.h>
#include <string>
#include "keyfinder.h"
#include "audiodata.h"

struct KeyFinderHandle {
    KeyFinder::KeyFinder* kf;
};

extern "C" {

EMSCRIPTEN_KEEPALIVE
KeyFinderHandle* keyfinder_create() {
    KeyFinderHandle* h = new KeyFinderHandle();
    h->kf = new KeyFinder::KeyFinder();
    return h;
}

EMSCRIPTEN_KEEPALIVE
void keyfinder_destroy(KeyFinderHandle* handle) {
    if (handle) {
        delete handle->kf;
        delete handle;
    }
}

EMSCRIPTEN_KEEPALIVE
const char* keyfinder_detect_key(KeyFinderHandle* handle, const float* samples, int sampleCount, int sampleRate) {
    if (!handle || !handle->kf || !samples || sampleCount <= 0) return nullptr;

    static std::string result;

    try {
        KeyFinder::AudioData audio;
        audio.setFrameRate(sampleRate);
        audio.setChannels(1);
        audio.addToSampleCount(sampleCount);
        for (int i = 0; i < sampleCount; i++) {
            audio.setSample(i, samples[i]);
        }

        KeyFinder::key_t key = handle->kf->keyOfAudio(audio);

        switch (key) {
            case KeyFinder::A_MAJOR: result = "A"; break;
            case KeyFinder::A_MINOR: result = "Am"; break;
            case KeyFinder::B_FLAT_MAJOR: result = "Bb"; break;
            case KeyFinder::B_FLAT_MINOR: result = "Bbm"; break;
            case KeyFinder::B_MAJOR: result = "B"; break;
            case KeyFinder::B_MINOR: result = "Bm"; break;
            case KeyFinder::C_MAJOR: result = "C"; break;
            case KeyFinder::C_MINOR: result = "Cm"; break;
            case KeyFinder::D_FLAT_MAJOR: result = "Db"; break;
            case KeyFinder::D_FLAT_MINOR: result = "Dbm"; break;
            case KeyFinder::D_MAJOR: result = "D"; break;
            case KeyFinder::D_MINOR: result = "Dm"; break;
            case KeyFinder::E_FLAT_MAJOR: result = "Eb"; break;
            case KeyFinder::E_FLAT_MINOR: result = "Ebm"; break;
            case KeyFinder::E_MAJOR: result = "E"; break;
            case KeyFinder::E_MINOR: result = "Em"; break;
            case KeyFinder::F_MAJOR: result = "F"; break;
            case KeyFinder::F_MINOR: result = "Fm"; break;
            case KeyFinder::G_FLAT_MAJOR: result = "Gb"; break;
            case KeyFinder::G_FLAT_MINOR: result = "Gbm"; break;
            case KeyFinder::G_MAJOR: result = "G"; break;
            case KeyFinder::G_MINOR: result = "Gm"; break;
            case KeyFinder::A_FLAT_MAJOR: result = "Ab"; break;
            case KeyFinder::A_FLAT_MINOR: result = "Abm"; break;
            default: result = "???"; break;
        }
        return result.c_str();
    } catch (...) {
        return nullptr;
    }
}

} // extern "C"
