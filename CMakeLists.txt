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

###################
#  Documentation  #
###################

find_package(Doxygen)
if(DOXYGEN_FOUND)
    option(${PROJECT_NAME}_BUILD_DOC "Generate API documentation with Doxygen" OFF)
    if(${PROJECT_NAME}_BUILD_DOC)
        configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in.cmake ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(
            ${PROJECT_NAME}_doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
            SOURCES ${PROJECT_SOURCE_DIR}/Doxyfile.in.cmake
        )
    endif()
endif()
