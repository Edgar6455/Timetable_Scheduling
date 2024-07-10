cmake_minimum_required(VERSION 3.10)
project(Timetabling)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/*.cpp")
list(REMOVE_ITEM SOURCE_FILES "${CMAKE_SOURCE_DIR}/source/main.cpp")
file(GLOB INCLUDE_FILES "${CMAKE_SOURCE_DIR}/include/*.hpp")

add_subdirectory(external/json)
add_subdirectory(source)
add_subdirectory(test)

set(SAMPLES_PATH ${CMAKE_SOURCE_DIR}/samples)
set(TEST_PATH ${CMAKE_SOURCE_DIR}/test)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})

target_compile_definitions(Timetabling PRIVATE SAMPLES_PATH="${SAMPLES_PATH}")
target_compile_definitions(Test PRIVATE TEST_PATH="${TEST_PATH}")

install(TARGETS Timetabling Test
        RUNTIME DESTINATION bin)