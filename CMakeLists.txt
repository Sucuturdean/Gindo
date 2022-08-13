cmake_minimum_required(VERSION 3.20)
project(gindo C)

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG c18851f52ec9704eb06464058a600845ec1eada1
)

add_library(gindo src/gindo.c)
add_executable(gindo_test src/main.c)

FetchContent_MakeAvailable(glfw)

target_compile_features(gindo PUBLIC c_std_99)
target_include_directories(gindo PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(gindo PRIVATE glfw)
target_link_libraries(gindo_test PRIVATE gindo)
