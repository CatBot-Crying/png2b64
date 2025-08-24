cmake_minimum_required(VERSION 3.16)
project(png64 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch cxxopts library ---
include(FetchContent)
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(cxxopts)

# --- Create executable ---
add_executable(png64
    main.cpp
    base64.h
    base64.cpp
)

# Link libraries
target_link_libraries(png64 PRIVATE cxxopts::cxxopts)

# Optional: Add compiler flags for optimization
target_compile_options(png64 PRIVATE -O3)
