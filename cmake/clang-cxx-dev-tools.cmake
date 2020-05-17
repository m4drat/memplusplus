# Additional targets to perform clang-format/clang-tidy
# Get all project files
file(GLOB_RECURSE
     ALL_CXX_SOURCE_FILES
     *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI]
     )

set(EXCLUDE_PATTERNS ${EXCLUDE_PATTERNS} "/CMakeFiles/" "cmake" "build" "3rd_party" ".git")

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
        --
        -std=c++17
        ${INCLUDE_DIRECTORIES}
        # -I/mnt/c/Users/madrat/Desktop/projects/memplusplus/libmemplusplus/include/ 
        # -I/usr/lib/gcc/x86_64-linux-gnu/7/include/ #
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