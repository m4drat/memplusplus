# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI] *.inl *.tpp
     )

set(EXCLUDE_PATTERNS ${EXCLUDE_PATTERNS} "/CMakeFiles/" "cmake" "build" "3rd_party" ".git" "tests")

# Delete exclude patterns
foreach (SOURCE_FILE ${ALL_CXX_SOURCE_FILES}) 
    foreach (EXCLUDE_PATTERN ${EXCLUDE_PATTERNS})
        string(FIND ${SOURCE_FILE} ${EXCLUDE_PATTERN} EXCLUDE_FOUND) 
        if (NOT ${EXCLUDE_FOUND} EQUAL -1) 
            list(REMOVE_ITEM ALL_CXX_SOURCE_FILES ${SOURCE_FILE})
        endif () 
    endforeach ()
endforeach ()

# Adding clang-format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT}
        -i
        -style=file
        ${ALL_CXX_SOURCE_FILES}
    )
endif()

# Find all headers for all projects
# get_target_property(MPP_INCLUDES mpp INCLUDE_DIRECTORIES)
# if (MPP_BUILD_FUZZER)
#     get_target_property(FUZZING_HARNESS_INCLUDES fuzzer INCLUDE_DIRECTORIES)
# endif()
# if (MPP_BUILD_EXAMPLE)
#     get_target_property(EXAMPLE_PROJECT_INCLUDES example_project INCLUDE_DIRECTORIES)
# endif()

# foreach(dir ${MPP_INCLUDES} ${FUZZING_HARNESS_INCLUDES} ${EXAMPLE_PROJECT_INCLUDES})
#     string(APPEND PROJECTS_INCLUDE_DIRS "-I${dir} ")
# endforeach()

set(EXAMPLE_PROJECT_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/example_project/include)
set(FUZZING_HARNESS_INCLUDES ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/fuzzer/include)
set(LIBMEMPLUSPLUS_INCLUDES  ${ALL_INCLUDE_DIRECTORIES} ${PROJECT_SOURCE_DIR}/libmemplusplus/include)

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy-15")
if(CLANG_TIDY)
    add_custom_target(
        clang-tidy
        COMMAND ${CLANG_TIDY}
        ${ALL_CXX_SOURCE_FILES}
        -checks=clang-analyzer-*,cppcoreguidelines*,performance-*,portability-*,readability-*
        --
        -std=c++17
        -I${EXAMPLE_PROJECT_INCLUDES}
        -I${FUZZING_HARNESS_INCLUDES}
        -I${LIBMEMPLUSPLUS_INCLUDES}
    )
endif()

# Adding clang-tidy target if executable is found
find_program(CLANG_STATIC_ANALYZER "scan-build")
if(CLANG_STATIC_ANALYZER)
    add_custom_target(
        clang-static-analyzer
        COMMAND ${CLANG_STATIC_ANALYZER} ./build.sh
    )
endif()