project (fig-cli)

debug_message()

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_executable(fig-cli ${headers} ${cppfiles})
target_link_libraries(fig-cli fig-core)