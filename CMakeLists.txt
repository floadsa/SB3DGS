cmake_minimum_required(VERSION 3.10)

project(SB3DGS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SOURCE_FILES
    src/main.cpp
    src/launcher.cpp
    src/initer.cpp
    src/gl_utils.cpp
    src/Models/mesh.cpp
    src/Models/scene.cpp
    src/Models/object.cpp
    src/Models/camera.cpp
    src/Models/UI/image.cpp
    src/Models/UI/text.cpp
    src/Models/UI/button.cpp
    src/glad.c
)

add_executable(SB3DGS ${SOURCE_FILES})

target_link_libraries(SB3DGS glfw GL)
