project(MultiThreadExample)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/${CMAKE_BUILD_TYPE})

include_directories(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(MultiThreadExample src/main.cpp)

