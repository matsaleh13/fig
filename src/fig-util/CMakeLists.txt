project (fig-util)

debug_message()

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_library(fig-util STATIC ${headers} ${cppfiles})
