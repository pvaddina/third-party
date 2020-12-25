cmake_minimum_required(VERSION 3.5)
project(g3log-wrapper-1)

set(CMAKE_PREFIX_PATH "../../../install/g3log-wrapper/static/${CMAKE_BUILD_TYPE}")

find_package(g3log-wrapper REQUIRED)
find_package(Threads REQUIRED)

add_executable(g3log-wrapper-1 main.cpp)

target_link_libraries(g3log-wrapper-1
PRIVATE
  g3log-wrapper
)


