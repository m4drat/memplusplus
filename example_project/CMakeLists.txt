project(example_project)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
	DEBUG_POSTFIX "-${STATIC_POSTFIX}d"
	RELEASE_POSTFIX "-${STATIC_POSTFIX}r"
	MINSIZEREL_POSTFIX "-${STATIC_POSTFIX}mr"
    RELWITHDEBINFO_POSTFIX "-${STATIC_POSTFIX}rd"
)

target_compile_options(${PROJECT_NAME} PRIVATE -g -O0)
target_link_libraries(${PROJECT_NAME} PRIVATE lib::mpp -export-dynamic)