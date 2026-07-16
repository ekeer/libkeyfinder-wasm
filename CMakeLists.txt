cmake_minimum_required(VERSION 3.16)
project(libkeyfinder-core CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
add_library(libkeyfinder-core STATIC
    libkeyfinder/src/audiodata.cpp
    libkeyfinder/src/chromagram.cpp
    libkeyfinder/src/chromatransform.cpp
    libkeyfinder/src/chromatransformfactory.cpp
    libkeyfinder/src/downsampler.cpp
    libkeyfinder/src/fftadapter.cpp
    libkeyfinder/src/keyclassifier.cpp
    libkeyfinder/src/keyfinder.cpp
    libkeyfinder/src/lowpassfilter.cpp
    libkeyfinder/src/lowpassfilterfactory.cpp
    libkeyfinder/src/parameters.cpp
    libkeyfinder/src/ringbuffer.cpp
    libkeyfinder/src/seg.cpp
    libkeyfinder/src/segarbitrary.cpp
    libkeyfinder/src/segcosine.cpp
    libkeyfinder/src/segnone.cpp
    libkeyfinder/src/spectrumanalyser.cpp
    libkeyfinder/src/temporalwindowfactory.cpp
    libkeyfinder/src/toneprofiles.cpp
    libkeyfinder/src/windowfunctions.cpp
    libkeyfinder/src/workspace.cpp
    src/keyfinder_wrapper.cpp
)

target_include_directories(libkeyfinder-core PUBLIC
    libkeyfinder/src
    src
)

target_link_libraries(libkeyfinder-core PUBLIC fftw3)
