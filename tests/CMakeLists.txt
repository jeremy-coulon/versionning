cmake_minimum_required(VERSION 2.8)

option(Versionning_BUILD_TEST "Build tests" ${BUILD_ALL})

if(Versionning_BUILD_TEST)

    project(TestVersionning CXX)

    find_package(Boost REQUIRED unit_test_framework)
    mark_as_advanced(Boost_DIR)

    set(PROJECT_SRC_DIR
        ${PROJECT_SOURCE_DIR}/src
    )

    set(${PROJECT_NAME}_FILES
        ${PROJECT_SRC_DIR}/main.cpp
        ${PROJECT_SRC_DIR}/testComparisonOperators.cpp
        ${PROJECT_SRC_DIR}/testStringConversions.cpp
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
