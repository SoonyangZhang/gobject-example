include_directories(${CMAKE_SOURCE_DIR}/base)
set(base_LIB 
thread.c
irunnable.c
print.c
timeutils.c
netutils.cc
)
add_library(base STATIC ${base_LIB})
