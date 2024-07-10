cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

file(GLOB TEST_SOURCE_FILES "${CMAKE_SOURCE_DIR}/test/source/*.cpp")

add_subdirectory(external/gtest)

add_executable(Test
        ${TEST_SOURCE_FILES}
        TestContents.hpp

        ${SOURCE_FILES}
        ${INCLUDE_FILES}
)

target_include_directories(Test PUBLIC ../include)
target_link_libraries(Test PRIVATE gtest gtest_main nlohmann_json::nlohmann_json)
