CXX=/usr/local/clang_9.0.0/bin/clang++ cmake -S . -B build \
	-DCMAKE_BUILD_TYPE=Debug \
	-DMPP_BUILD_FUZZER=OFF \
	-DMPP_BUILD_EXAMPLE=ON \
	-DMPP_BUILD_TESTS=OFF \
	-DMPP_BUILD_DOCS=OFF \
	-DMPP_BUILD_BENCHMARK=OFF \
	-DCMAKE_EXPORT_COMPILE_COMMANDS=OFF \
	-DMPP_SANITIZERS=OFF \
	-DMPP_BUILD_SHARED_LIBS=OFF \
	-DMPP_FULL_DEBUG=ON \
	-DMPP_SECURE=OFF \
	-DMPP_PROFILE=ON \
	-DMPP_COLOUR=ON \
	-DMPP_STATS=ON

CXX=/usr/local/clang_9.0.0/bin/clang++ cmake --build build --config Debug --target all
