# Slot-Engine

## Build

- Install a C++20 toolchain (MSYS2 mingw64 or Visual Studio with g++/clang).
- Install GLFW 3.4+ and GLEW 2.1+ either via a package manager (recommended: vcpkg, Conan) or by downloading their SDK archives.
- Configure the project with CMake from the repo root:
	- If using vcpkg: `cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"`
	- If using unpacked SDKs: point the cache variables at the top-level folders that contain both `include/` and `lib/`, e.g. `cmake -S . -B build -DGLFW_ROOT="C:/glfw-3.4.0.bin.WIN64" -DGLEW_ROOT="C:/glew-2.1.0"`
- Build with `cmake --build build`.
- Copy the matching `glew32.dll` and `glfw3.dll` next to `build/bin/main.exe` before running the executable.