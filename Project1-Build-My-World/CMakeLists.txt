cmake_minimum_required(VERSION 3.10)

project(WelcomePlugin)

find_package(gazebo REQUIRED)

include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
list(APPEND CMAKE_CXX_FLAGS "${GAZEBO_CXX_FLAGS}")

add_library(welcome SHARED script/first_gazebo.cpp)
target_link_libraries(welcome ${GAZEBO_LIBRARIES})

