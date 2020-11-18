cmake_minimum_required(VERSION 3.10.2)
project(sealvm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11 -Wall -Wno-long-long -pedantic")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# ---------------------------------
# SealASM parser type checks
add_custom_target(SEALASM_PARSER_TYPE_CHECK ALL "mypy" "${CMAKE_BINARY_DIR}/cmd/sealasm/sealasm.py")
# ---------------------------------

# ---------------------------------
# LIBS
# libsealvm
file(GLOB LIBSEALVM_SRC "${CMAKE_BINARY_DIR}/src/sealvm/*.c")
add_library(libsealvm SHARED ${LIBSEALVM_SRC})
set_target_properties(libsealvm PROPERTIES LINKER_LANGUAGE C)
# ---------------------------------

# ---------------------------------
# EXECUTABLES
# sealvm
file(GLOB SEALVM_SRC "${CMAKE_BINARY_DIR}/cmd/sealvm/sealvm.c")
add_executable(sealvm ${SEALVM_SRC})
target_link_libraries(sealvm libsealvm)
set_target_properties(sealvm PROPERTIES LINKER_LANGUAGE C)
# ---------------------------------

include_directories(
    "${CMAKE_BINARY_DIR}/include"
)