#
# Find Valgrind.
#
# This module defines:
# Valgrind_INCLUDE_DIR, where to find valgrind/memcheck.h, etc.
# Valgrind_PROGRAM, the valgrind executable.
# Valgrind_FOUND, If false, do not try to use valgrind.
#
# If you have valgrind installed in a non-standard place, you can define
# VALGRIND_PREFIX to tell cmake where it is.

include(FindPackageHandleStandardArgs)

find_path(Valgrind_INCLUDE_DIR valgrind.h
    /usr/include
    /usr/include/valgrind
    /usr/local/include
    /usr/local/include/valgrind
    ${VALGRIND_PREFIX}/include
    ${VALGRIND_PREFIX}/include/valgrind)

find_program(Valgrind_PROGRAM NAMES valgrind PATH
    /usr/bin
    /usr/local/bin
    ${VALGRIND_PREFIX}/bin)

find_package_handle_standard_args(Valgrind DEFAULT_MSG
    Valgrind_INCLUDE_DIR
    Valgrind_PROGRAM)

mark_as_advanced(Valgrind_INCLUDE_DIR Valgrind_PROGRAM)
