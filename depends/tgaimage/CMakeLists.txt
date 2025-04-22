include_directories(${CMAKE_CURRENT_LIST_DIR})
file(GLOB SOURCES "*.h" "*.cpp")
add_library(tgaimage ${SOURCES})