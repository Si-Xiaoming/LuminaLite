cmake_minimum_required(VERSION 3.20)
project(LuminaLite LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
if(MSVC)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif(MSVC)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_AUTORCC ON)
include_directories(${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/depends)

add_subdirectory(src)
add_subdirectory(depends)

# 如果在${PROJECT_SOURCE_DIR}/data的目录下没有".obj"的文件
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/data/models/african_head.obj")
# 设置代理（如果需要）
set(ENV{HTTP_PROXY} "http://127.0.0.1:10809")
set(ENV{HTTPS_PROXY} "http://127.0.0.1:10809")
# 从下载文件到"${PROJECT_SOURCE_DIR}/data/"
set(MODEL_URL "https://github.com/ssloy/tinyrenderer/raw/f6fecb7ad493264ecd15e230411bfb1cca539a12/obj/african_head.obj")  # 替换为实际模型URL
set(MODEL_PATH "${PROJECT_SOURCE_DIR}/data/models")   # 下载到构建目录下的models文件夹

file(MAKE_DIRECTORY ${MODEL_PATH})
file(DOWNLOAD ${MODEL_URL}
     ${MODEL_PATH}/african_head.obj
     SHOW_PROGRESS
     STATUS DOWNLOAD_STATUS

)
# 检查下载状态
list(GET DOWNLOAD_STATUS 0 STATUS_CODE)
if(NOT STATUS_CODE EQUAL 0)
    message(FATAL_ERROR "下载失败，状态码: ${STATUS_CODE}")
endif()
endif()