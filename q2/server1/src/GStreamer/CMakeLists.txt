cmake_minimum_required(VERSION 3.0)

project(streamer)

set(CMAKE_C_STANDARD 11)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0 gstreamer-app-1.0)

add_executable(streamer streamer.c)

target_include_directories(streamer PRIVATE ${GST_INCLUDE_DIRS})
target_compile_options(streamer PRIVATE ${GST_CFLAGS_OTHER})
target_link_libraries(streamer PRIVATE ${GST_LIBRARIES} -lgstapp-1.0 -lgstreamer-1.0)