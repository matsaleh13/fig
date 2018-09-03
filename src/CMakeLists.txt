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

# Add sub-project folders
add_subdirectory(fig-util)
add_subdirectory(fig-core)
add_subdirectory(fig-coredyn)
add_subdirectory(fig-cli)

# Files
#file(GLOB util-headers fig-util/*.h)
#file(GLOB util-cppfiles fig-util/*.cpp)
#file(GLOB core-headers fig-core/*.h)
#file(GLOB core-cppfiles fig-core/*.cpp)
#file(GLOB coredyn-headers fig-coredyn/*.h)
#file(GLOB coredyn-cppfiles fig-coredyn/*.cpp)
#file(GLOB cli-headers fig-cli/*.h)
#file(GLOB cli-cppfiles fig-cli/*.cpp)

# Binary targets
#add_library(fig-core STATIC ${core-headers} ${core-cppfiles})
#add_library(fig-coredyn SHARED ${coredyn-headers} ${coredyn-cppfiles})
#add_executable(fig-cli ${cli-headers} ${cli-cppfiles})

# Dependencies
#add_dependencies(fig-cli fig-coredyn fig-core)
#add_dependencies(fig-coredyn fig-core)
