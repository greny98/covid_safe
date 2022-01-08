cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "covid_safe")

project(${PROJECT_NAME} VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES} src/lite.cpp include/lite.h include/box_utils.h src/box_utils.cpp src/bounding_box.cpp include/bounding_box.h)
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
  target_link_libraries(${PROJECT_NAME} /usr/local/lib/libuvc.dylib tensorflowlite)
else()
  message("Linux config")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lm -ldl")
  # target_link_libraries(${PROJECT_NAME} ${CMAKE_DL_LIBS})
  include_directories(/home/pi/workspace/tflite-dist/include)
  target_link_libraries(${PROJECT_NAME} /usr/local/lib/libuvc.so)

  ADD_LIBRARY(tensorflowlite STATIC IMPORTED)
  set_property(TARGET tensorflowlite PROPERTY IMPORTED_LOCATION /home/pi/workspace/tflite-dist/lib/libtensorflow-lite.a)
  target_link_libraries(${PROJECT_NAME} tensorflowlite)
endif ()

target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS})
