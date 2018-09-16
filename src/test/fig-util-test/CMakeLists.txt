project (fig-util-test)

debug_message()

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_executable(fig-util-test ${headers} ${cppfiles})
target_link_libraries(fig-core fig-util)
