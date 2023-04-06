cmake_minimum_required(VERSION 3.24)
project(cpp_vk_lessons)

set(CMAKE_CXX_STANDARD 17)

find_package(Catch2 3 REQUIRED)


add_executable(${PROJECT_NAME}
        main.cpp memory_structure.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
