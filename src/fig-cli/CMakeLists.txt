project (fig-cli)

message ("DEBUG INFO...")
message ("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message ("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message ("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_executable(fig-cli ${headers} ${cppfiles})
target_link_libraries(fig-cli fig-core)