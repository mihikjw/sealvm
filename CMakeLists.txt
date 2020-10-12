cmake_minimum_required(VERSION 3.10.2)
project(sealvm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

include_directories(
    "${CMAKE_BINARY_DIR}/include"
)

file(GLOB SOURCES
    "${CMAKE_BINARY_DIR}/cmd/*.cpp"
    "${CMAKE_BINARY_DIR}/src/sealvm/*.cpp"
)

add_executable(sealvm ${SOURCES})