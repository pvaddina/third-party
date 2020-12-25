cmake_minimum_required(VERSION 3.5)
project(spdlog_filelogger)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "../../../install/spdlog/static/${CMAKE_BUILD_TYPE}")

find_package(spdlog CONFIG REQUIRED)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  spdlog::spdlog
  Threads::Threads
)


