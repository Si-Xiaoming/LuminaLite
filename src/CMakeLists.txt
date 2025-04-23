add_subdirectory(basicRender)
add_subdirectory(rayCaster)

file(COPY ${PROJECT_SOURCE_DIR}/data/models DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)