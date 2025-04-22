file(GLOB SOURCES "*.h" "*.cpp")
add_executable(basicRender ${SOURCES})
target_link_libraries(basicRender tgaimage)
