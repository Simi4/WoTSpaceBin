cmake_minimum_required(VERSION 3.22)

project(openwg_spacebin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build test programs" OFF)

add_library(${PROJECT_NAME}
    "src/common/array.cpp"
    "src/sections/section_bsma.cpp"
    "src/sections/section_bsmo.cpp"
    "src/sections/section_bsmi.cpp"
    "src/sections/section_bwst.cpp"
    "src/sections/section_bwt2.cpp"
    "src/spacebin.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC "include")

if(BUILD_TESTS)
    add_executable(openwg_spacebin_test
        "tests/main.cpp"
    )
    target_link_libraries(openwg_spacebin_test ${PROJECT_NAME})
endif(BUILD_TESTS)
