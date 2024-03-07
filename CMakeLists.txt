cmake_minimum_required(VERSION 3.27.0)
project(GENERIC_HASH_TABLE C CXX)

# I want this to be portable
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_C_STANDARD                20)
set(CMAKE_CXX_STANDARD_REQUIRED    NO)
set(CMAKE_CXX_EXTENSIONS           OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

set(Headers
    hashtable.hpp
)

set(Sources
    hashtable.cpp
)


add_library( ${PROJECT_NAME} STATIC ${Sources} ${Headers} )

add_subdirectory(test)