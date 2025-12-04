# Slot-Engine

## Build

- Install a C++20 toolchain (MSYS2 mingw64 or Visual Studio with g++/clang).
- Install GLFW 3.4+ and GLEW 2.1+ either via a package manager (recommended: vcpkg, Conan) or by downloading their SDK archives.
- Configure the project with CMake from the repo root:
	- If using vcpkg: `cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"`
	- If using unpacked SDKs: point the cache variables at the top-level folders that contain both `include/` and `lib/`, e.g. `cmake -S . -B build -DGLFW_ROOT="C:/glfw-3.4.0.bin.WIN64" -DGLEW_ROOT="C:/glew-2.1.0"`
- Build with `cmake --build build`.
- Copy the matching `glew32.dll` and `glfw3.dll` next to `build/bin/main.exe` before running the executable.

## Project Layout

- `src/app/` – entry points, lifecycle glue, configuration loading.
- `src/render/` – OpenGL helpers, draw routines, shader management.
- `src/slot/` – mathematical slot model, RNG, payout evaluation.
- `config/` – machine setup files (JSON/TOML) once defined.
- `assets/` – textures, audio, fonts, and reel data under `assets/reels/`.
- `shaders/` – GLSL vertex/fragment programs.
- `docs/` – design notes, math model references, developer logs.
- `tests/` – statistical and regression test harnesses.
- `third_party/` – dependency acquisition notes and license summaries.