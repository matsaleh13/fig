cmake_minimum_required( VERSION 3.9.2 )
project(test)

debug_message()

# These steps from: https://www.testcookbook.com/book/cpp/setting-up-cmake-google-test.html

set(CMAKE_CXX_STANDARD 11)

# Download and unpack googletest at configure time
configure_file(
        CMakeLists.txt.in
        googletest-download/CMakeLists.txt
)
# message("execute_process(COMMAND ${CMAKE_COMMAND} -G \"${CMAKE_GENERATOR}\" .
#         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )")
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )

# message("execute_process(COMMAND ${CMAKE_COMMAND} --build .
#         WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/googletest-download )


# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${PROJECT_BINARY_DIR}/googletest-src
       ${PROJECT_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
   include_directories("${gtest_SOURCE_DIR}/include"
           "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate

enable_testing()
add_subdirectory(fig-util-test)

