cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER "dpcpp") 
set(CMAKE_LINKER "dpcpp")
set(CMAKE_CXX_STANDARD 17)

project(helix-solver)

add_subdirectory(libs/googletest)
add_subdirectory(libs/json)

file(GLOB SOURCES
        "include/HelixSolver/*.h"
        "src/*.cpp")

find_package(Boost)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
