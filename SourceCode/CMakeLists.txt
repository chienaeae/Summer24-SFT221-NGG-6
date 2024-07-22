cmake_minimum_required(VERSION 3.1.0)

project(app LANGUAGES C)

include_directories(Project/*.h)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG=1)
  message("Debug mode enabled")
endif()

add_executable(main Project/main.c Project/mapping.c Project/shipment.c
                    Project/utils.c)

# Link the math library on non-Windows systems
if(NOT WIN32)
  target_link_libraries(main m)
endif()
