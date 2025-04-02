cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_executable(tune_me
        main.cpp

        ${SOURCE_FILES}
        ${INCLUDE_FILES}
)

target_include_directories(tune_me PUBLIC ../include)
target_link_libraries(tune_me PRIVATE nlohmann_json::nlohmann_json)
