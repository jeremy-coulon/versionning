cmake_minimum_required(VERSION 2.8)

set(CMAKE_USER_MAKE_RULES_OVERRIDE ${CMAKE_CURRENT_LIST_DIR}/DefaultBuildFlags.cmake)

add_subdirectory(test)
add_subdirectory(example)
