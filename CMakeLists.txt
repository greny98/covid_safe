cmake_minimum_required(VERSION 3.10)
set(CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME "covid_safe")

project(${PROJECT_NAME} VERSION 1.0)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
find_package(OpenCV REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_FILES} src/uvc_com.cpp include/uvc_com.h)
target_include_directories(
  ${PROJECT_NAME} PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  /usr/local/include/libuvc
)
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${OpenCV_LIBS}
  /usr/local/lib/libuvc.dylib
  #    /usr/local/lib/libuvc.so
  )
