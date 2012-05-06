cmake_minimum_required(VERSION 2.8)

project(Versionning CXX)

######################
#  Global variables  #
######################

# Set project version
include(version.cmake)
message(STATUS "${PROJECT_NAME} v${${PROJECT_NAME}_VERSION}")

# Set install path (relative path only)
set(INSTALL_INCLUDE_DIR include)
set(INSTALL_CMAKE_DIR share/${PROJECT_NAME}/cmake)
set(INSTALL_DOC_DIR share/doc/${PROJECT_NAME})

#############
#  Sources  #
#############

set(PROJECT_INCLUDE_DIR
    ${PROJECT_SOURCE_DIR}/include
)

set(PROJECT_FILES
    ${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/Version.h
    ${PROJECT_INCLUDE_DIR}/${PROJECT_NAME}/VersionException.h
)

add_custom_target(
    ${PROJECT_NAME}
    COMMAND ""
    SOURCES ${PROJECT_FILES}
)

####################
#  Subdirectories  # 
####################

add_subdirectory(share)

###############
#  Packaging  #
###############

# Package include directory
install(DIRECTORY
    ${PROJECT_INCLUDE_DIR}/
    DESTINATION ${INSTALL_INCLUDE_DIR}
    COMPONENT dev
)

###########
#  CPack  #
###########

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
