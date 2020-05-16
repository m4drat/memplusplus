project(unit_tests)

# add the CMakeFile that defines catch2
add_subdirectory(3rd_party/catch2)

# Add a testing executable
add_executable(unit_tests unit_tests.cpp)

target_link_libraries(${PROJECT_NAME}
    lib::mpp
    Catch2::Test
)

add_test(test_all ${CMAKE_BINARY_DIR}/binaries/bin/${PROJECT_NAME})