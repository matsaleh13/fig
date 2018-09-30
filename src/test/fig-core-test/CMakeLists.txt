project (fig-core-test)

debug_boilerplate()
debug_message("fig_core_include: ${fig_core_include}")

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

warnings_strict()

add_executable(fig-core-test ${headers} ${cppfiles})
target_link_libraries(fig-core-test fig-core gtest gmock_main)
target_include_directories(fig-core-test PRIVATE ${fig_core_include} ${fig_util_include})

add_test(NAME fig_core_test COMMAND fig-core-test)