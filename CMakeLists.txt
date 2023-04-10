cmake_minimum_required(VERSION 3.23)

project(BunnyEngine LANGUAGES C CXX ASM VERSION 0.1.0 DESCRIPTION "The Bunny 2D Game Engine!")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(util/out-of-source-build)

add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Bunny)