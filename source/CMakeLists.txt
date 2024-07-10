cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

add_executable(Timetabling
        main.cpp

        ${SOURCE_FILES}
        ${INCLUDE_FILES}
)

target_include_directories(Timetabling PUBLIC ../include)
target_link_libraries(Timetabling PRIVATE nlohmann_json::nlohmann_json)
