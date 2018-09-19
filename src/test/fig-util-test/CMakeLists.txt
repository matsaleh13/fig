project (fig-util-test)

debug_message()
message("fig_util_include: ${fig_util_include}")

file(GLOB headers *.h)
file(GLOB cppfiles *.cpp)

add_executable(fig-util-test ${headers} ${cppfiles})
target_link_libraries(fig-util-test fig-util gtest gmock_main)
target_include_directories(fig-util-test PRIVATE ${fig_util_include})

add_test(NAME fig_util_test COMMAND fig-util-test)