# CMakeList.txt for HAL
#   Build a library (`hal`) which exposes the header files as "hal/*.h"
#   Use header as: #include "hal/button.h"

include_directories(HAL/include)
file(GLOB MY_SOURCES "src/*.c")

add_library(HAL STATIC ${MY_SOURCES})

target_include_directories(HAL PUBLIC include)
