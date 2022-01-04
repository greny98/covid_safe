cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "covid_safe")

project(${PROJECT_NAME} VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(
  ${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${OpenCV_INCLUDE_DIRS}
  /usr/local/include/libuvc
)

if (APPLE)
  message("Mac config")
  include_directories(/Users/tuannguyen/workspace/tflite-dist/include)
  ADD_LIBRARY(tensorflowlite SHARED IMPORTED)
  set_property(TARGET tensorflowlite PROPERTY IMPORTED_LOCATION
    /Users/tuannguyen/workspace/tflite-dist/libs/mac/libtensorflowlite.dylib)
  target_link_libraries(${PROJECT_NAME} /usr/local/lib/libuvc.dylib)
else()
  message("Linux config")
  target_link_libraries(${PROJECT_NAME} /usr/local/lib/libuvc.so)
  include_directories(/home/pi/workspace/tflite-dist/include)
  ADD_LIBRARY(tensorflowlite SHARED IMPORTED)
  set_property(TARGET tensorflowlite PROPERTY IMPORTED_LOCATION
    /home/pi/workspace/tflite-dist/lib/libtensorflow-lite.a)
  
endif ()

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
  tensorflowlite)
