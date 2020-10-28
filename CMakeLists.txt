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
# LIBS
# libsealvm
file(GLOB LIBSEALVM_SRC "${CMAKE_BINARY_DIR}/src/sealvm/*.cpp")
add_library(libsealvm SHARED ${LIBSEALVM_SRC})
set_target_properties(libsealvm PROPERTIES LINKER_LANGUAGE CXX)

# libparser
file(GLOB LIBPARSER_SRC "${CMAKE_BINARY_DIR}/src/parser/*.cpp")
add_library(libparser SHARED ${LIBPARSER_SRC})
set_target_properties(libparser PROPERTIES LINKER_LANGUAGE CXX)

# libsealasm
file(GLOB LIBSEALASM_SRC "${CMAKE_BINARY_DIR}/src/sealasm/*.cpp")
add_library(libsealasm SHARED ${LIBSEALASM_SRC})
set_target_properties(libsealasm PROPERTIES LINKER_LANGUAGE CXX)
# ---------------------------------

# ---------------------------------
# EXECUTABLES
# sealvm
file(GLOB SEALVM_SRC "${CMAKE_BINARY_DIR}/cmd/sealvm/sealvm.cpp")
add_executable(sealvm ${SEALVM_SRC})
target_link_libraries(sealvm libsealvm)
set_target_properties(sealvm PROPERTIES LINKER_LANGUAGE CXX)

# parser
file(GLOB PARSER_SRC "${CMAKE_BINARY_DIR}/cmd/sealasm/parser.cpp")
add_executable(parser ${PARSER_SRC})
target_link_libraries(parser libsealasm libparser)
set_target_properties(parser PROPERTIES LINKER_LANGUAGE CXX)
# ---------------------------------

include_directories(
    "${CMAKE_BINARY_DIR}/include"
)