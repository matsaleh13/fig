project (fig-coredyn)

debug_boilerplate()

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_library(fig-coredyn SHARED ${headers} ${cppfiles})
target_link_libraries(fig-coredyn fig-core)