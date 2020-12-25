cmake_minimum_required(VERSION 3.5)
project(g3log_default_and_custom)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "../../../install/g3log/static/${CMAKE_BUILD_TYPE}")

find_package(g3log CONFIG REQUIRED)
message(
"g3log package:
    found: ${G3LOG_FOUND}
    include dir: ${G3LOG_INCLUDE_DIRS}
    libraries: ${G3LOG_LIBRARIES}"
)

include_directories(${G3LOG_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  ${G3LOG_LIBRARIES}
)


