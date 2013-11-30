cmake_minimum_required(VERSION 2.8)

set(${PROJECT_NAME}_MAJOR 0)
set(${PROJECT_NAME}_MINOR 0)
set(${PROJECT_NAME}_PATCH 3)
set(${PROJECT_NAME}_TWEAK 4)

set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_MAJOR}.${${PROJECT_NAME}_MINOR}.${${PROJECT_NAME}_PATCH}.${${PROJECT_NAME}_TWEAK}")
find_package(Git)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE ${PROJECT_NAME}_VERSION_STRING
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    string(FIND ${${PROJECT_NAME}_VERSION_STRING} ${${PROJECT_NAME}_VERSION} substring_found)
    if(substring_found EQUAL -1)
        message(FATAL_ERROR "Version mismatch: ${${PROJECT_NAME}_VERSION_STRING} != ${${PROJECT_NAME}_VERSION}")
    endif()
else()
    set(${PROJECT_NAME}_VERSION_STRING "v${${PROJECT_NAME}_VERSION}")
endif()
