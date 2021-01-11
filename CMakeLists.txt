cmake_minimum_required(VERSION 3.19.2) 
project(test)									

set ( APP_NAME test )

set( CMAKE_BUILD_TYPE RELEASE )

include_directories (C:/opencv/opencv/build/include)

link_directories ( C:/opencv/opencv/build/x64/vc15/lib/)

add_executable(test test.cpp)	

target_link_libraries( ${APP_NAME} opencv_world343.lib )

