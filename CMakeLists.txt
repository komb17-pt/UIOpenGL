cmake_minimum_required(VERSION 3.10.0)
project(uiopengl VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SDL2 root directory with libraries and include files
set(SDL2_DIR "/Users/pt/Code/vcpkg/installed/arm64-osx")

add_compile_definitions(
    VERTEX_SHADER_PATH=\"${CMAKE_SOURCE_DIR}/shaders/vertex.glsl\"
    FRAGMENT_SHADER_PATH=\"${CMAKE_SOURCE_DIR}/shaders/fragment.glsl\"
)

include_directories(${SDL2_DIR}/include/SDL2)
include_directories(${SDL2_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

add_executable(uiopengl
    src/main.cpp
    src/Renderer.cpp
    src/Scene.cpp
    src/Object.cpp
    src/Button.cpp
    src/Shader.cpp
)

target_link_libraries(uiopengl PRIVATE SDL2::SDL2 SDL2::SDL2main) # SDL2::SDL2-static
target_link_libraries(uiopengl PRIVATE glm::glm-header-only)
target_link_libraries(uiopengl PRIVATE glad::glad)
