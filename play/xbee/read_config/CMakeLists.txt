cmake_minimum_required(VERSION 3.5)
project(read_config)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH "../../../install/yaml-cpp/static/${CMAKE_BUILD_TYPE}")

find_package(yaml-cpp CONFIG REQUIRED)

include_directories("../../../install/xbee/include"
                    "../../../install/xbee/ports/posix")

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
PRIVATE
  yaml-cpp
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/config.yaml $<TARGET_FILE_DIR:${PROJECT_NAME}>)
