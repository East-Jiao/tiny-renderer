cmake_minimum_required(VERSION 3.16)
project(renderer LANGUAGES CXX)

set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RENDERER_SOURCE src/main.cpp
                    src/renderer/framebuffer.cpp)

set(IO_SOURCE src/io/image_io.cpp
              src/io/model/obj.cpp)

add_executable(${PROJECT_NAME} ${RENDERER_SOURCE} ${IO_SOURCE})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/includes)