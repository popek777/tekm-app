cmake_minimum_required (VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)

project (tekm-app)

add_executable(tekm-app
  main.cpp
  HttpsUtils.cpp
  AppUtils.cpp
)

target_link_libraries(tekm-app pthread)

find_package(OpenSSL)
if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})
  target_link_libraries(tekm-app ${OPENSSL_LIBRARIES})
endif()

set(BOOST_ROOT               "${CMAKE_SOURCE_DIR}/thirdparty/boost_1_66_0")
set(Boost_USE_STATIC_LIBS    ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS     OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS   ON)  # only find release libs
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.66 COMPONENTS system REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(tekm-app ${Boost_LIBRARIES})
endif()

include_directories("${CMAKE_SOURCE_DIR}/thirdparty/json/include")
include_directories("${CMAKE_SOURCE_DIR}/thirdparty/fifo_map/src")

