cmake_minimum_required (VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

project (tekm-app)

add_executable(tekm-app 
  main.cpp
  )

target_link_libraries(tekm-app pthread)

install (TARGETS tekm-app DESTINATION bin)
