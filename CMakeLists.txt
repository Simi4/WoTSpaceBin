cmake_minimum_required(VERSION 3.15)

project(openwg_spacebin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(openwg_spacebin
    "include/common/array.h"
	"include/common/typedefs.h"

	"include/sections/section_bsma.h"
	"src/sections/section_bsma.cpp"

	"include/sections/section_bwal.h"
	"src/sections/section_bwal.cpp"

	"include/sections/section_bwcs.h"
	"src/sections/section_bwcs.cpp"

    "include/sections/section_bwst.h"
	"src/sections/section_bwst.cpp"

	"include/sections/section_bwwa.h"
	"src/sections/section_bwwa.cpp"

	"include/sections/section_wgsd.h"
	"src/sections/section_wgsd.cpp"

    "src/spacebin.cpp"
)

target_include_directories(openwg_spacebin PUBLIC "include")

add_executable(openwg_spacebin_test
    "tests/main.cpp"
)
target_link_libraries(openwg_spacebin_test openwg_spacebin)
