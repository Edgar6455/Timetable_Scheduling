cmake_minimum_required(VERSION 3.10)
project(Timetabling)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/*.cpp")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/main.cpp")
file(GLOB INCLUDE_FILES "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_subdirectory(external/json)
add_subdirectory(source)

set(SAMPLES_PATH ${CMAKE_SOURCE_DIR}/samples)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

target_compile_definitions(tune_me PRIVATE SAMPLES_PATH="${SAMPLES_PATH}")

install(TARGETS tune_me
        RUNTIME DESTINATION bin)