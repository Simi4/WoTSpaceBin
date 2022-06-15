cmake_minimum_required(VERSION 3.22)

project(openwg_spacebin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME}
    "include/common/array.h"
    "include/common/typedefs.h"

    "include/sections/section_bsma.h"
    "src/sections/section_bsma.cpp"

    "include/sections/section_bsmo.h"
    "src/sections/section_bsmo.cpp"

    "include/sections/section_bwst.h"
    "src/sections/section_bwst.cpp"

    "src/spacebin.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC "include")

add_executable(openwg_spacebin_test
    "tests/main.cpp"
)
target_link_libraries(openwg_spacebin_test ${PROJECT_NAME})
