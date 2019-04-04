include_directories(${CMAKE_SOURCE_DIR}/boy)
include_directories(${CMAKE_SOURCE_DIR}/base)
set(boy_LIB 
boy.c
man.c
signal-demo.c
iusb.c
udisk.c
ianimal.c
human.c
my_parent.c
my_child.c
my_add.c
my_list.c
my_add_child.c
)
add_library(boy STATIC ${boy_LIB})
