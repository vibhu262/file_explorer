
cmake_minimum_required(VERSION 3.19)

project(FileManager_2
    VERSION 1.0.0
    DESCRIPTION "Native Qt C++ File Manager"
    LANGUAGES CXX
)

# C++ configuration
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Qt modules
find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
)

# Enable Qt automatic code generation
qt_standard_project_setup()

# Application executable
qt_add_executable(FileManager_2
    WIN32
    MACOSX_BUNDLE

    # Entry point
    src/main.cpp

    # Main window
    src/mainwindow.cpp
    include/mainwindow.h
    forms/mainwindow.ui

    # File manager tab
    src/filemanagertab.cpp
    include/filemanagertab.h
    forms/filemanagertab.ui

    # Data models
    src/filetabmodel.cpp
    include/filetabmodel.h

    src/filetreemodel.cpp
    include/filetreemodel.h
    .gitignore
)

# Header file search path
target_include_directories(FileManager_2
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# UI file search path for AUTOUIC
set_target_properties(FileManager_2 PROPERTIES
    AUTOUIC_SEARCH_PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/forms"
)

# Link Qt libraries
target_link_libraries(FileManager_2
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

# Compiler-specific warnings
if(MSVC)
    target_compile_options(FileManager_2 PRIVATE
        /W4
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(FileManager_2 PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# Installation rules
include(GNUInstallDirs)

install(TARGETS FileManager_2
    BUNDLE DESTINATION .
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

# Generate the Qt deployment script for Windows
qt_generate_deploy_app_script(
    TARGET FileManager_2
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT "${deploy_script}")
