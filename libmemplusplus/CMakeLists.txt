add_library(${PROJECT_NAME} SHARED "") # add_library(${PROJECT_NAME} SHARED "")

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "%<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>" # ${CMAKE_INSTALL_PREFIX}/include
)

# if (NOT BUILD_SHARED_LIBS)   # if we are building not shared lib
#     set(STATIC_POSTFIX "-s") # static postfix
# endif()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    DEBUG_POSTFIX          "-${STATIC_POSTFIX}d" # debug postfix
    RELEASE_POSTFIX        "-${STATIC_POSTFIX}r" # release postfix
    MINSIZEREL_POSTFIX     "-${STATIC_POSTFIX}rm"  # release minsize postfix
    RELWITHDEBINFO_POSTFIX "-${STATIC_POSTFIX}rdi" # release with debug info postfix
)

add_subdirectory("include")
add_subdirectory("src")
# add_subdirectory("tests")