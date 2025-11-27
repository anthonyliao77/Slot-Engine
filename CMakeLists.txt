cmake_minimum_required(VERSION 3.20)
project(SlotEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)

find_package(glfw3 CONFIG QUIET)
if(TARGET glfw AND NOT TARGET glfw3::glfw3)
	add_library(glfw3::glfw3 ALIAS glfw)
endif()

if(NOT TARGET glfw3::glfw3)
	set(GLFW_ROOT "" CACHE PATH "Path to the GLFW install root (contains include/ and lib/)" )
	find_path(GLFW_INCLUDE_DIR
		NAMES GLFW/glfw3.h
		HINTS ${GLFW_ROOT} $ENV{GLFW_ROOT} $ENV{GLFW_DIR}
		PATH_SUFFIXES include include/GLFW
	)
	find_library(GLFW_LIBRARY
		NAMES glfw3 glfw3dll libglfw3dll
		HINTS ${GLFW_ROOT} $ENV{GLFW_ROOT} $ENV{GLFW_DIR}
		PATH_SUFFIXES lib lib-mingw-w64 lib-mingw lib64
	)
	if(NOT GLFW_INCLUDE_DIR OR NOT GLFW_LIBRARY)
		message(FATAL_ERROR "GLFW not found. Install a package that ships CMake configs (e.g. vcpkg) or set GLFW_ROOT to your SDK location.")
	endif()

	add_library(glfw3::glfw3 UNKNOWN IMPORTED)
	set_target_properties(glfw3::glfw3 PROPERTIES
		IMPORTED_LOCATION "${GLFW_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${GLFW_INCLUDE_DIR}"
	)
endif()

find_package(GLEW CONFIG QUIET)
if(TARGET GLEW::glew AND NOT TARGET GLEW::GLEW)
	add_library(GLEW::GLEW ALIAS GLEW::glew)
endif()

if(NOT TARGET GLEW::GLEW)
	set(GLEW_ROOT "" CACHE PATH "Path to the GLEW install root (contains include/ and lib/)" )
	find_path(GLEW_INCLUDE_DIR
		NAMES GL/glew.h
		HINTS ${GLEW_ROOT} $ENV{GLEW_ROOT} $ENV{GLEW_DIR}
		PATH_SUFFIXES include
	)
	find_library(GLEW_LIBRARY
		NAMES glew32 glew32s libglew32
		HINTS ${GLEW_ROOT} $ENV{GLEW_ROOT} $ENV{GLEW_DIR}
		PATH_SUFFIXES lib lib/Release/x64 lib64
	)
	if(NOT GLEW_INCLUDE_DIR OR NOT GLEW_LIBRARY)
		message(FATAL_ERROR "GLEW not found. Install a package that ships CMake configs (e.g. vcpkg) or set GLEW_ROOT to your SDK location.")
	endif()

	add_library(GLEW::GLEW UNKNOWN IMPORTED)
	set_target_properties(GLEW::GLEW PROPERTIES
		IMPORTED_LOCATION "${GLEW_LIBRARY}"
		INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIR}"
	)
endif()

add_executable(main src/main.cpp)

target_link_libraries(main PRIVATE
	glfw3::glfw3
	GLEW::GLEW
	OpenGL::GL
)

set_target_properties(main PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
	RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)
