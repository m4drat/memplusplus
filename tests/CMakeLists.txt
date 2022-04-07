project(unit_tests)

# Add a testing executable
add_executable(unit_tests 
    gc_graph_tests.cpp
    shared_gcptr_tests.cpp
    chunk_treap_test.cpp
    allocator_logic_tests.cpp
    # security_tests.cpp # CATCH2 doesn't support catching of Abort signal 🤷‍♀️
)

target_link_libraries(${PROJECT_NAME}
    lib::mpp
    Catch2::Catch2WithMain
)

add_test(unit_tester ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME})