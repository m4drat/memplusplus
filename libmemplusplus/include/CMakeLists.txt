set(FILES "")
set(SUBDIRECTORIES "mpp")
set(RELATIVE_PATH "include")

# add all subdirectories
foreach(VAR ${SUBDIRECTORIES})
    add_subdirectory(${VAR})
endforeach()

# there are files in subdirectories
if(FILES)
    # add source files to target 
    target_sources(${PROJECT_NAME} PRIVATE ${FILES})

    install(FILES ${FILES} DESTINATION ${RELATIVE_PATH})
endif()