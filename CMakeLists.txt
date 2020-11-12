cmake_minimum_required(VERSION 3.10.2)
project(sealvm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
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
# libsealvm-cpp
file(GLOB LIBSEALVM_CPP_SRC "${CMAKE_BINARY_DIR}/src/sealvm-cpp/*.cpp")
add_library(libsealvm-cpp SHARED ${LIBSEALVM_CPP_SRC})
set_target_properties(libsealvm-cpp PROPERTIES LINKER_LANGUAGE CXX)

# libbinreader
file(GLOB LIBBINREADER_SRC "${CMAKE_BINARY_DIR}/src/binreader/*.cpp")
add_library(libbinreader SHARED ${LIBBINREADER_SRC})
set_target_properties(libbinreader PROPERTIES LINKER_LANGUAGE CXX)
# ---------------------------------

# ---------------------------------
# EXECUTABLES
# sealvm-cpp
file(GLOB SEALVM_CPP_SRC "${CMAKE_BINARY_DIR}/cmd/sealvm/sealvm.cpp")
add_executable(sealvm-cpp ${SEALVM_CPP_SRC})
target_link_libraries(sealvm-cpp libsealvm-cpp libbinreader)
set_target_properties(sealvm-cpp PROPERTIES LINKER_LANGUAGE CXX)

# sealdbg
file(GLOB SEALDBG_SRC "${CMAKE_BINARY_DIR}/cmd/sealdbg/sealdbg.cpp")
add_executable(sealdbg ${SEALDBG_SRC})
target_link_libraries(sealdbg libsealvm-cpp libbinreader)
set_target_properties(sealdbg PROPERTIES LINKER_LANGUAGE CXX)
# ---------------------------------

include_directories(
    "${CMAKE_BINARY_DIR}/include"
)