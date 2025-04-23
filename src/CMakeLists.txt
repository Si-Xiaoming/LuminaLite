add_subdirectory(basicRender)
# ½«"${PROJECT_SOURCE_DIR}/data/models"¸´ÖÆµ½"${CMAKE_CURRENT_BINARY_DIR}/data/models"
file(COPY ${PROJECT_SOURCE_DIR}/data/models DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)