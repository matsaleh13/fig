project (fig-util)

debug_boilerplate()

file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB cppfiles ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(fig-util INTERFACE)

# Below only if we make this a static lib at some point (likely).
# add_library(fig-util STATIC ${headers} ${cppfiles})
# set_target_properties(fig-util PROPERTIES LINKER_LANGUAGE CXX)

# Export for access by others.
set(fig_util_include ${PROJECT_SOURCE_DIR} PARENT_SCOPE)

