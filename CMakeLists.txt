cmake_minimum_required(VERSION 3.12)
project(cppcraft LANGUAGES CXX C)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

add_subdirectory(src)
add_subdirectory(external)

file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
