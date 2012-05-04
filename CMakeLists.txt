project(Versionning CXX)

set(${PROJECT_NAME}_INCLUDE_DIR ${${PROJECT_NAME}_SOURCE_DIR}/include CACHE INTERNAL "")

set(${PROJECT_NAME}_FILES
    ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/Version.h
    ${${PROJECT_NAME}_INCLUDE_DIR}/${PROJECT_NAME}/VersionException.h
)

include_directories(
    ${${PROJECT_NAME}_INCLUDE_DIR}
)

add_custom_target(${PROJECT_NAME}
    COMMAND ""
    SOURCES ${${PROJECT_NAME}_FILES})
