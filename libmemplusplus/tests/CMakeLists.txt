project(unit_tests)

# add the CMakeFile that defines catch2
add_subdirectory(3rd_party/catch2)

# enable CTest testing
enable_testing()

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)

target_link_libraries(unit_tests
    lib::mpp
    Catch2::Test
)

add_test(test_all unit_tests)