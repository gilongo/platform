cmake_minimum_required(VERSION 3.10)
project(platform VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

include_directories(/opt/homebrew/include)
link_directories(/opt/Homebrew/lib)

add_executable(platform ${SOURCES})
target_include_directories(platform PRIVATE src src/heads)

target_link_libraries(platform sfml-graphics sfml-window sfml-system)