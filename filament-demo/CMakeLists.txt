cmake_minimum_required(VERSION 3.22)
project(filament-demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

add_library(filament-meta INTERFACE)
target_link_directories(filament-meta INTERFACE "./libs/filamentapp/lib-rel-linux-x86_64")
target_link_directories(filament-meta INTERFACE "./libs/filagui/lib-rel-linux-x86_64")
target_link_directories(filament-meta INTERFACE "./libs/third_party/imgui/lib-rel-linux-x86_64")
target_link_directories(filament-meta INTERFACE "./libs/third_party/libsdl2/lib-rel-linux-x86_64")
target_link_directories(filament-meta INTERFACE "./filament/lib-rel-linux-x86_64")

target_include_directories(filament-meta INTERFACE "./libs/filamentapp/include")
target_include_directories(filament-meta INTERFACE "./libs/third_party/libsdl2/include")
target_include_directories(filament-meta INTERFACE "./filament/include")
target_link_libraries(filament-meta INTERFACE filamentapp filamentapp-resources filament sdl2 backend bluevk bluegl vkshaders smol-v ibl-lite stb filaflat filagui imgui camutils ktxreader filament-iblprefilter image filabridge utils)

target_link_libraries(${PROJECT_NAME} PUBLIC openwg_spacebin filament-meta)
target_link_directories(${PROJECT_NAME} PUBLIC "../build")
target_include_directories(${PROJECT_NAME} PUBLIC "../include")
