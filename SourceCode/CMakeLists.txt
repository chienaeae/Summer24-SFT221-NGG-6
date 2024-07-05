cmake_minimum_required(VERSION 3.1.0)

project(app LANGUAGES C)

include_directories(Project/*.h)

add_executable(main Project/main.c Project/mapping.c)

# Link the math library on non-Windows systems
if(NOT WIN32)
  target_link_libraries(main m)
endif()
