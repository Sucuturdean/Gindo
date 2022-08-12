cmake_minimum_required(VERSION 3.20)
project(gindo C)

include(FetchContent)
include(ExternalProject)

find_program(MESON meson REQUIRED)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG c18851f52ec9704eb06464058a600845ec1eada1
)

ExternalProject_Add(
  libepoxy
  GIT_REPOSITORY https://github.com/anholt/libepoxy.git
  GIT_TAG a96abf1a4d29f78034273cbce96006cde950390c
  BINARY_DIR libepoxy-build
  SOURCE_DIR libepoxy-src
  CONFIGURE_COMMAND ${MESON} setup <SOURCE_DIR> --default-library=static
  BUILD_COMMAND ${MESON} compile -C <BINARY_DIR>
  INSTALL_COMMAND ""
)

add_library(gindo src/gindo.c)
add_executable(gindo_test src/main.c)

FetchContent_MakeAvailable(glfw)

ExternalProject_Get_Property(libepoxy SOURCE_DIR BINARY_DIR)

target_include_directories(gindo PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(gindo PRIVATE ${SOURCE_DIR}/include) # Source_dir is libepoxy's source directory
target_link_libraries(gindo PRIVATE glfw ${BINARY_DIR}/src/libepoxy.a)
target_link_libraries(gindo_test PRIVATE gindo)
