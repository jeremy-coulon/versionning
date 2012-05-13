# - Config file for the Versionning package
# It defines the following variables
#  Versionning_INCLUDE_DIR  - include directory for Versionning
#  Versionning_INCLUDE_DIRS - include directories for Versionning

@PACKAGE_INIT@

set(Versionning_INCLUDE_DIR 
    "@PACKAGE_CMAKE_INSTALL_FULL_INCLUDEDIR@"
    CACHE PATH "Include directory for Versionning"
)
if(Versionning_FIND_REQUIRED)
    set_and_check(Versionning_INCLUDE_DIRS "${Versionning_INCLUDE_DIR}")
else()
    set(Versionning_INCLUDE_DIRS "${Versionning_INCLUDE_DIR}")
endif()

mark_as_advanced(
    Versionning_DIR
    Versionning_INCLUDE_DIR
)
