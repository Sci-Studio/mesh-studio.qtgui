## MeshGenQtApp
A Qt Widget Application for displaying the 2D generated mesh from MeshGen library

## Requirements
- **CMake** ≥ 3.14
- **C++20** compiler (GCC 10+, Clang 12+, or MSVC with C++20)

## Build

```bash
cmake -S . -B build
cmake --build build
```

This produces:

- `build/MeshGenQtApp` — CLI

`CMAKE_EXPORT_COMPILE_COMMANDS` is enabled, so CMake also writes `build/compile_commands.json`.