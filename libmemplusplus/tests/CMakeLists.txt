project(unit_tests)

# add the CMakeFile that defines catch2
add_subdirectory(3rd_party/catch2)

# Add a testing executable
add_executable(unit_tests 
    test_main.cpp
    shared_gcptr_tests.cpp
    chunk_treap_test.cpp
)

target_link_libraries(${PROJECT_NAME}
    lib::mpp
    Catch2::Test
)

add_test(test_all ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})