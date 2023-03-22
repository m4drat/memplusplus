#!/bin/bash

if [ "$1" == "codeql" ]; then
	echo "Building for CodeQL"

	CXX=clang++ cmake -S . -B build \
		-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
		-DCMAKE_BUILD_TYPE=Debug \
		-DMPP_BUILD_FUZZER=ON \
		-DMPP_BUILD_EXAMPLE=ON \
		-DMPP_BUILD_TESTS=OFF \
		-DMPP_BUILD_DOCS=OFF \
		-DMPP_SANITIZERS=OFF \
		-DMPP_VALGRIND=OFF \
		-DMPP_BUILD_SHARED_LIBS=OFF \
		-DMPP_FULL_DEBUG=ON \
		-DMPP_SECURE=ON \
		-DMPP_PROFILE=ON \
		-DMPP_COLOUR=ON \
		-DMPP_STATS=ON

	CXX=clang++ cmake --build build --config Debug --target all -- -j 16

	exit 0
fi

CXX=clang++ cmake -S . -B build \
	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
	-DCMAKE_BUILD_TYPE=Debug \
	-DMPP_BUILD_FUZZER=ON \
	-DMPP_BUILD_EXAMPLE=ON \
	-DMPP_BUILD_TESTS=ON \
	-DMPP_BUILD_DOCS=OFF \
	-DMPP_SANITIZERS=ON \
	-DMPP_VALGRIND=OFF \
	-DMPP_BUILD_SHARED_LIBS=OFF \
	-DMPP_FULL_DEBUG=ON \
	-DMPP_SECURE=ON \
	-DMPP_PROFILE=ON \
	-DMPP_COLOUR=ON \
	-DMPP_STATS=OFF

CXX=clang++ cmake --build build --config Debug --target all -- -j 16
