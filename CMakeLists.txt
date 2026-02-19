cmake_minimum_required(VERSION 3.20)
project(SlotEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1. Find OpenGL (Standard CMake way)
find_package(OpenGL REQUIRED)

# 2. Find GLEW and GLFW (The Ubuntu/Linux way)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

# 3. Define the executable
add_executable(main src/main.cpp)

# 4. Link the libraries (.so files)
# This tells the linker which binaries to bundle
target_link_libraries(main PRIVATE
    ${GLFW_LIBRARIES}
    ${GLEW_LIBRARIES}
    OpenGL::GL
)

# 5. Set the include directories (.h files)
# This tells the compiler where to find <GLFW/glfw3.h> and <GL/glew.h>
target_include_directories(main PRIVATE
    ${GLFW_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

# 6. Output Directory Settings (Keeping your original logic)
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
