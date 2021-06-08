cmake_minimum_required(VERSION 3.17)
project(cal_proj)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

# include_directories("lib/GraphViewerCpp/SFML/include")
# link_directories("lib/GraphViewerCpp/SFML/lib")

add_subdirectory("lib/GraphViewerCpp")
include_directories("lib/GraphViewerCpp/include")

include_directories("include" "algorithms/include")

file(GLOB_RECURSE SRC "src/*.cpp" "algorithms/src/*.h")
add_executable(cal_proj ${SRC})

target_link_libraries(${PROJECT_NAME} graphviewer)
