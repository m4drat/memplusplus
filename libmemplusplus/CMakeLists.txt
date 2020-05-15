project(libmpp)

add_library(${PROJECT_NAME} src/mpp.cpp)
add_library(lib::libmpp ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)