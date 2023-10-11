cmake_minimum_required(VERSION 3.5.0)
project(28_3_kitchen_online VERSION 0.1.0 LANGUAGES C CXX)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(28_3_kitchen_online main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
