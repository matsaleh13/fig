cmake_minimum_required( VERSION 3.9.2 )

# Version info.
set (Fig_VERSION_MAJOR 0)
set (Fig_VERSION_MINOR 0)
set (Fig_VERSION_PATCH 1)

project (Fig VERSION ${Fig_VERSION_MAJOR}.${Fig_VERSION_MINOR}.${Fig_VERSION_PATCH} )

message ("DEBUG INFO...")
message ("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message ("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message ("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

# Pass CMake settings to source code.
configure_file (
    "${PROJECT_SOURCE_DIR}/FigConfig.h.in"
    "${PROJECT_BINARY_DIR}/FigConfig.h"
)

# Add binary tree to the search path for include files
# so that we'll find FigConfig.h.
include_directories("${PROJECT_BINARY_DIR}")

