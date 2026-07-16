cmake_minimum_required(VERSION 3.16)
project(libkeyfinder-core CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find FFTW3
find_library(FFTW3_LIB fftw3 PATHS $ENV{FFTW3_ROOT}/lib $ENV{FFTW3_ROOT}/lib64)
find_path(FFTW3_INCLUDE_DIR fftw3.h PATHS $ENV{FFTW3_ROOT}/include)

if(NOT FFTW3_LIB)
  message(FATAL_ERROR "FFTW3 library not found. Set FFTW3_ROOT or check build.")
endif()

message(STATUS "FFTW3 lib: ${FFTW3_LIB}")
message(STATUS "FFTW3 include: ${FFTW3_INCLUDE_DIR}")

file(GLOB KEYFINDER_SRC
    libkeyfinder/src/*.cpp
    src/keyfinder_wrapper.cpp
)

add_library(libkeyfinder-core STATIC ${KEYFINDER_SRC})
target_include_directories(libkeyfinder-core PUBLIC libkeyfinder/src src)
target_link_libraries(libkeyfinder-core PUBLIC ${FFTW3_LIB})
target_compile_options(libkeyfinder-core PRIVATE -Wno-psabi)
