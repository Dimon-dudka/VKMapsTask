cmake_minimum_required(VERSION 3.29)
project(VK_Maps_Task)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
        ${CMAKE_SOURCE_DIR}/FileReader/FileReader.h
        ${CMAKE_SOURCE_DIR}/PathFinder/PathFinder.h
        ${CMAKE_SOURCE_DIR}/VkMapsTaskStructure/TaskStructure.h
)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/main.cpp
        ${CMAKE_SOURCE_DIR}/FileReader/FileReader.cpp
        ${CMAKE_SOURCE_DIR}/PathFinder/PathFinder.cpp
        ${CMAKE_SOURCE_DIR}/VkMapsTaskStructure/TaskStructure.cpp
)

add_executable(VK_Maps_Task ${SOURCES} ${HEADERS})

target_include_directories(VK_Maps_Task
        PUBLIC ${CMAKE_SOURCE_DIR}
        PUBLIC ${CMAKE_SOURCE_DIR}/PathFinder
        PUBLIC ${CMAKE_SOURCE_DIR}/FileReader
        PUBLIC ${CMAKE_SOURCE_DIR}/VkMapsTaskStructure
)