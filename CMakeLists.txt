cmake_minimum_required(VERSION 3.14.0)
project(ctkDemo VERSION 0.1 LANGUAGES CXX)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/wd4996)
endif()

add_subdirectory(ctk)
add_subdirectory(App)
add_subdirectory(Plugins)