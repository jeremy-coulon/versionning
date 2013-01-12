cmake_minimum_required(VERSION 2.8)

option(Versionning_BUILD_TEST "Build tests" OFF)

if(Versionning_BUILD_TEST)

    project(VersionningTest CXX)

    find_package(Boost REQUIRED unit_test_framework)
    mark_as_advanced(Boost_DIR)

    set(${PROJECT_NAME}_FILES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/testComparisonOperators.cpp
        ${PROJECT_SOURCE_DIR}/testStringConversions.cpp
    )

    include_directories(
        ${Versionning_INCLUDE_DIR}
        ${Boost_INCLUDE_DIR}
    )

    add_definitions(-DBOOST_TEST_DYN_LINK)

    add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_FILES})

    target_link_libraries(${PROJECT_NAME}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    )

endif()
