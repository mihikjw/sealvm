#!/bin/bash
# script to clean build artifacts and generated files
if [ -f ./Makefile ]; then make clean; fi;
if [ -d ./CMakeFiles ]; then rm -r ./CMakeFiles; fi;
if [ -f ./cmake_install.cmake ]; then rm ./cmake_install.cmake; fi;
if [ -f ./CMakeCache.txt ]; then rm ./CMakeCache.txt; fi;
if [ -f ./compile_commands.json ]; then rm ./compile_commands.json; fi;
if [ -f ./Makefile ]; then rm ./Makefile; fi;