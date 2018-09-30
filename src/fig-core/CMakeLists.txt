project (fig-core)

debug_boilerplate()
debug_message("fig_util_include: ${fig_util_include}")

file(GLOB headers ${PROJECT_SOURCE_DIR}/*.h)
file(GLOB cppfiles ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories(${fig_util_include})
add_library(fig-core INTERFACE)
target_link_libraries(fig-core INTERFACE fig-util)

# Below only if we make this a static lib at some point (likely).
# add_library(fig-core STATIC ${headers} ${cppfiles})
# set_target_properties(fig-core PROPERTIES LINKER_LANGUAGE CXX)

# Export for access by others.
set(fig_core_include ${PROJECT_SOURCE_DIR} PARENT_SCOPE)