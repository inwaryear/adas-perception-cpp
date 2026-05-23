cmake_minimum_required(VERSION 3.22)
project(adas_perception VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

# NOTE : Usage of pkg-config when a library has no CMake configuration file but reading at the documentation,
#        PCL has a CMake config
find_package(PCL REQUIRED)

add_library(adas_core INTERFACE)
add_library(adas_utils INTERFACE)
add_library(adas_com INTERFACE)

target_include_directories(adas_core 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_include_directories(adas_utils 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_include_directories(adas_com 
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )


add_executable(adas_perception src/main.cpp)

target_link_libraries(adas_perception 
    PRIVATE
        adas_core 
        adas_utils 
        adas_com
    )

target_include_directories(adas_perception PRIVATE ${PCL_INCLUDE_DIRS})
target_compile_definitions(adas_perception PRIVATE ${PCL_DEFINITIONS})
target_link_libraries(adas_perception PRIVATE ${PCL_LIBRARIES})