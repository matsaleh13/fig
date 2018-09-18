project (fig-util)

debug_message()

file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB cppfiles ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(fig-util STATIC ${headers} ${cppfiles})
set_target_properties(fig-util PROPERTIES LINKER_LANGUAGE CXX)

# Export for access by others.
set(fig_util_include ${PROJECT_SOURCE_DIR} PARENT_SCOPE)
set(fig_util_sources ${headers} ${cppfiles} PARENT_SCOPE)

