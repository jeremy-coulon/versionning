cmake_minimum_required(VERSION 2.8)

project(Versionning CXX)

set(${PROJECT_NAME}_INCLUDE_DIR
    ${${PROJECT_NAME}_SOURCE_DIR}/include
    CACHE INTERNAL ""
)

set(${PROJECT_NAME}_FILES
    ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/Version.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/VersionException.h
)

add_custom_target(
    ${PROJECT_NAME}
    COMMAND ""
    SOURCES ${${PROJECT_NAME}_FILES}
)
