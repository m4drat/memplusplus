project(example_project)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories( ${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries( ${PROJECT_NAME}
	lib::libmpp
)