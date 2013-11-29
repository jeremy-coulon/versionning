cmake_minimum_required(VERSION 2.8)

option(Versionning_BUILD_EXAMPLE "Build examples" ${BUILD_ALL})

if(Versionning_BUILD_EXAMPLE)

    project(VersionningExample CXX)

    ##################
    #  Dependencies  #
    ##################

    find_package(Boost REQUIRED)
    mark_as_advanced(Boost_DIR)

    #######################
    #  Compilation flags  #
    #######################

    include_directories(
        ${Versionning_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
    )

    #############
    #  Sources  #
    #############

    set(PROJECT_SRC_DIR
        ${PROJECT_SOURCE_DIR}/src
    )

    ############
    #  Target  #
    ############

    add_executable(${PROJECT_NAME} ${PROJECT_SRC_DIR}/example.cpp)

endif()
