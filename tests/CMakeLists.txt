project(unit_tests)

list(APPEND MPP_TESTS_SOURCES
    test_main.cpp
    gc_tests.cpp
    gc_graph_tests.cpp
    shared_gcptr_tests.cpp
    chunk_treap_test.cpp
    allocator_logic_tests.cpp
    security_tests.cpp # Hurray, after migrating to gtest we finally can test for abort signal!
)

if(MPP_SANITIZERS MATCHES "ON")
    message(STATUS "Sanitizers are enabled, adding asan tests")
    list(APPEND MPP_TESTS_SOURCES asan_tests.cpp)
endif()

# Add a testing executable
add_executable(unit_tests
    ${MPP_TESTS_SOURCES}
)

if(MPP_SANITIZERS MATCHES "ON")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0 -fsanitize=address)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC mpp::mpp gtest -Wl,--export-dynamic)

add_test(unit_tester ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})