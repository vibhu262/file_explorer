# Modular File Manager

A lightweight, high-performance file manager built with standard C++17 and Qt6. The project bypasses heavy Qt filesystem models in favor of a custom, vector-backed architecture using `std::filesystem` for fast OS queries and strict memory control.

## Features
* **Lazy-Loaded Directory Tree:** Custom `QAbstractItemModel` that only allocates memory and scans the disk when a directory is actively expanded by the user.
* **Vector-Backed Table View:** Custom `QAbstractTableModel` utilizing `std::vector` for raw C++ struct management and fast flat-data rendering.
* **Native Path Navigation:** Directory traversal managed entirely by C++ standard path parsing.
* **Modular Architecture:** Clean separation of `src/` and `include/` directories, isolating UI configuration from the systems backend.

## Running the Release (Windows)
1. Navigate to the **Releases** section on the right side of the GitHub repository.
2. Download the latest `.zip` file under **Assets** (e.g., `v0.1.0-alpha`).
3. Extract the `.zip` archive to a folder on your machine.
4. Double-click `FileManager_2.exe` to run the application. *Note: All required Qt `.dll` dependencies are already bundled in the folder via `windeployqt`, so Qt does not need to be installed on the host machine.*

## Building from Source
**Prerequisites:** 
* CMake 3.16 or higher
* A C++17 compatible compiler (MSVC, GCC, or Clang)
* Qt6 with the Widgets module

```bash
# 1. Clone the repository
git clone [https://github.com/YourUsername/YourRepoName.git](https://github.com/YourUsername/YourRepoName.git)
cd YourRepoName

# 2. Configure the CMake build system
mkdir build && cd build
cmake ..

# 3. Compile the optimized release binary
cmake --build . --config Release
