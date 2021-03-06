cmake_minimum_required( VERSION 3.9.2 )

# Macros
include("./macros.cmake")

# Version info.
set (Fig_VERSION_MAJOR 0)
set (Fig_VERSION_MINOR 0)
set (Fig_VERSION_PATCH 1)

project (Fig VERSION ${Fig_VERSION_MAJOR}.${Fig_VERSION_MINOR}.${Fig_VERSION_PATCH} )
debug_boilerplate()

# Compiler settings.
set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
warnings_strict()

# Pass CMake settings to source code.
configure_file (
    "${PROJECT_SOURCE_DIR}/FigConfig.h.in"
    "${PROJECT_BINARY_DIR}/FigConfig.h"
)

# Add binary tree to the search path for include files
# so that we'll find FigConfig.h.
include_directories("${PROJECT_BINARY_DIR}")

# Add sub-project folders
add_subdirectory(fig-util)
add_subdirectory(fig-core)
add_subdirectory(fig-coredyn)
add_subdirectory(fig-cli)
add_subdirectory(test)

