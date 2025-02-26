cmake_minimum_required(VERSION 3.5)

project(format-string-check LANGUAGES CXX)

include(CTest)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(format-string-check)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
