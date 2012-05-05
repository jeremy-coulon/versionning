cmake_minimum_required(VERSION 2.8)

project(Versionning CXX)

include(version.cmake)
message(STATUS "${PROJECT_NAME} v${${PROJECT_NAME}_VERSION}")

#############
#  Sources  #
#############

set(${PROJECT_NAME}_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include
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
        file(COPY ${PROJECT_SOURCE_DIR}/LICENSE_1_0.txt DESTINATION ${PROJECT_BINARY_DIR})
        configure_file(${PROJECT_SOURCE_DIR}/Doxyfile.in.cmake ${PROJECT_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(
            ${PROJECT_NAME}_doc
            ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
            SOURCES ${PROJECT_SOURCE_DIR}/Doxyfile.in.cmake
        )
    endif()
endif()

###############
#  Packaging  #
###############

# Offer the user the choice of overriding the installation directories
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKE_DIR share/${PROJECT_NAME}/cmake CACHE PATH "Installation directory for CMake files")
set(INSTALL_DOC_DIR share/doc/${PROJECT_NAME} CACHE PATH "Installation directory for documentation")

# Package include directory
install(DIRECTORY
    ${${PROJECT_NAME}_INCLUDE_DIR}/
    DESTINATION ${INSTALL_INCLUDE_DIR}
    COMPONENT dev
)

# Make relative paths absolute (needed later on)
foreach(p INCLUDE CMAKE)
    set(var INSTALL_${p}_DIR)
    if(NOT IS_ABSOLUTE "${${var}}")
        set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif()
endforeach()

# Create the VersionningConfig.cmake and VersionningConfigVersion files
file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
     "${INSTALL_INCLUDE_DIR}")
configure_file(VersionningConfig.cmake.in
    "${PROJECT_BINARY_DIR}/VersionningConfig.cmake" @ONLY)
configure_file(VersionningConfigVersion.cmake.in
    "${PROJECT_BINARY_DIR}/VersionningConfigVersion.cmake" @ONLY)

# Package CMake files
file(RELATIVE_PATH 
    INSTALL_CMAKE_DIR 
    "${CMAKE_INSTALL_PREFIX}"
    "${INSTALL_CMAKE_DIR}"
)
install(FILES
    ${PROJECT_BINARY_DIR}/VersionningConfig.cmake
    ${PROJECT_BINARY_DIR}/VersionningConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKE_DIR}
    COMPONENT dev
)

# Package documentation
install(FILES
    ${PROJECT_SOURCE_DIR}/LICENSE_1_0.txt
    DESTINATION ${INSTALL_DOC_DIR}
    COMPONENT doc
)
if(${PROJECT_NAME}_BUILD_DOC)
    install(DIRECTORY
        ${PROJECT_BINARY_DIR}/html
        DESTINATION ${INSTALL_DOC_DIR}
        COMPONENT doc
    )
endif()

# CPack configuration
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(UNIX)
    set(CPACK_GENERATOR "TGZ")
endif()
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple portable C++ data structure to store versionning information of a project.")
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE_1_0.txt")
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}_v${${PROJECT_NAME}_VERSION}")

include(CPack)
