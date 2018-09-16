project (fig-core)

debug_message()

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_library(fig-core STATIC ${headers} ${cppfiles})