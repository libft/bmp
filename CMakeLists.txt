cmake_minimum_required(VERSION 2.8.12)
project(ft_bmp C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
if (CMAKE_C_COMPILER_ID MATCHES \"Clang\" OR CMAKE_COMPILER_IS_GNUCC)
  add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()
if (MSVC)
  add_compile_options(/W4 /WX /wd4200)
endif()

include_directories(include)

file(GLOB_RECURSE SRC "src/*.c")
add_library(ft_bmp STATIC ${SRC})
