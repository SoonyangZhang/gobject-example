PROJECT(project)
cmake_minimum_required(VERSION 2.6)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall  -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall  -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -O2")
set(CMAKE_CXX_FLAGS "-fPIC")  
set(CMAKE_C_FLAGS "-fPIC") 
add_definitions(-D__STDC_FORMAT_MACROS)
#add_definitions(-DNDEBUG)
add_definitions(-std=c++11  )#-fno-rtti
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")


##https://www.jianshu.com/p/46e9b8a6cb6a
##https://github.com/gammu/gammu/tree/master/cmake
find_package(Glib)
find_package(GObject)
include_directories(${CMAKE_SOURCE_DIR}/)
include_directories(${Glib_INCLUDE_DIRS} ${GObject_INCLUDE_DIRS})


include_directories(${CMAKE_SOURCE_DIR}/boy)
add_subdirectory(boy)
include_directories(${CMAKE_SOURCE_DIR}/base)
add_subdirectory(base)

set(EXECUTABLE_NAME "man")
add_executable(${EXECUTABLE_NAME} boy/boy-test.c)
target_link_libraries(${EXECUTABLE_NAME}  boy ${Glib_LIBRARIES} ${GObject_LIBRARIES})


set(EXECUTABLE_NAME "peek")
add_executable(${EXECUTABLE_NAME} boy/peek.c)
target_link_libraries(${EXECUTABLE_NAME}  boy ${Glib_LIBRARIES} ${GObject_LIBRARIES})

#http://garfileo.is-programmer.com/2011/3/25/gobject-signal-extra-1.25576.html
set(EXECUTABLE_NAME "signal")
add_executable(${EXECUTABLE_NAME} boy/signal-test.c)
target_link_libraries(${EXECUTABLE_NAME}  boy ${Glib_LIBRARIES} ${GObject_LIBRARIES})

set(EXECUTABLE_NAME "thread")
add_executable(${EXECUTABLE_NAME} base/thread-test.c)
target_link_libraries(${EXECUTABLE_NAME}  base ${Glib_LIBRARIES} ${GObject_LIBRARIES} pthread)

set(EXECUTABLE_NAME "disk")
add_executable(${EXECUTABLE_NAME} boy/disk-test.c)
target_link_libraries(${EXECUTABLE_NAME}  boy ${Glib_LIBRARIES} ${GObject_LIBRARIES})

