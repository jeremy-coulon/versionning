cmake_minimum_required(VERSION 2.8)

##########################
#  CMake exported files  #
##########################

project(VersionningCMake)

include(CMakePackageConfigHelpers)

# Generate VersionningConfig.cmake
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/VersionningConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/VersionningConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
    PATH_VARS CMAKE_INSTALL_FULL_INCLUDEDIR
)

# Generate VersionningConfigVersion.cmake
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/VersionningConfigVersion.cmake
    VERSION ${Versionning_VERSION}
    COMPATIBILITY ExactVersion
)

###############
#  Packaging  #
###############

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/VersionningConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/VersionningConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_CMAKEDIR}
    COMPONENT dev
)
