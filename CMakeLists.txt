CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(ST7735s_lib)

INCLUDE_DIRECTORIES (
        ./include
)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O2")
SET(CMAKE_C_COMPILER arm-opi-linux-gnueabihf-gcc)
SET(CMAKE_CXX_COMPILER arm-opi-linux-gnueabihf-g++)


ADD_LIBRARY ( 
        ST7735s_lib STATIC
        src/Display.cpp
        src/Object.cpp
        src/Buzzer.cpp
)

TARGET_LINK_LIBRARIES (
        ST7735s_lib
)

ADD_EXECUTABLE (
        ST7735s_demo
        src/demo.cpp
)

ADD_LIBRARY(ST7735s_libd STATIC IMPORTED)

SET_TARGET_PROPERTIES (
        ST7735s_libd PROPERTIES
        IMPORTED_LOCATION ./libST7735s_lib.a
)

TARGET_LINK_LIBRARIES (
        ST7735s_demo ST7735s_libd
)
