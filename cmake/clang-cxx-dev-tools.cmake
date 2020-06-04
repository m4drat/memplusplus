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

# Adding clang-tidy target if executable is found
find_program(CLANG_TIDY "clang-tidy")
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

# macro(print_all_variables)
#     message(STATUS "print_all_variables------------------------------------------{")
#     get_cmake_property(_variableNames VARIABLES)
#     foreach (_variableName ${_variableNames})
#         message(STATUS "${_variableName}=${${_variableName}}")
#     endforeach()
#     message(STATUS "print_all_variables------------------------------------------}")
# endmacro()

# print_all_variables()