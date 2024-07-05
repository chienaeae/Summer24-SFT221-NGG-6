cmake_minimum_required(VERSION 3.1.0)

project(app LANGUAGES C)

include_directories(Project/*.h)

add_executable(main Project/main.c Project/mapping.c)
