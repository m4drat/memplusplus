project(unit_tests)

# Add a testing executable
add_executable(unit_tests
    test_main.cpp
    gc_tests.cpp
    gc_graph_tests.cpp
    shared_gcptr_tests.cpp
    chunk_treap_test.cpp
    allocator_logic_tests.cpp
    security_tests.cpp # Hurray, after migrating to gtest we finally can test for abort signal!
    asan_tests.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC lib::mpp gtest)

if(MPP_SANITIZERS MATCHES "ON")
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O2 -fsanitize=address)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -g -O2)
endif()

add_test(unit_tester ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})