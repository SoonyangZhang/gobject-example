include_directories(${CMAKE_SOURCE_DIR}/boy)
set(boy_LIB 
boy.c
man.c
signal-demo.c
iusb.c
udisk.c
ianimal.c
human.c
)
add_library(boy STATIC ${boy_LIB})
