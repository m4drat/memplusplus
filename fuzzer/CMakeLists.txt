project(fuzzer)

################# SET FUZZER SOURCES #################
list(APPEND MPP_FUZZER_SOURCES
	src/main.cpp
	src/tokenizer.cpp
)

add_executable(${PROJECT_NAME} ${MPP_FUZZER_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_compile_options(${PROJECT_NAME} PRIVATE -g -O1 -fsanitize=fuzzer,address)
target_link_libraries(${PROJECT_NAME} PRIVATE lib::mpp -fsanitize=fuzzer)
# target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
# target_link_libraries(${PROJECT_NAME} PRIVATE lib::mpp)