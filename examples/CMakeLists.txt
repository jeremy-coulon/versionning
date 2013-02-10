cmake_minimum_required(VERSION 2.8)

option(Versionning_BUILD_EXAMPLE "Build examples" OFF)

if(Versionning_BUILD_EXAMPLE)

    project(VersionningExample CXX)

    find_package(Boost REQUIRED)
    mark_as_advanced(Boost_DIR)

    include_directories(
        ${Versionning_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
    )

    set(PROJECT_SRC_DIR
        ${PROJECT_SOURCE_DIR}/src
    )

    add_executable(${PROJECT_NAME} ${PROJECT_SRC_DIR}/example.cpp)
    
endif()
