cmake_minimum_required(VERSION 3.14)

project(zxcmodule VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR_PLATFORM x64)

file(GLOB_RECURSE SOURCES "src/**.cpp")
file(GLOB_RECURSE HEADERS "src/**.h" "src/**.hpp")

include_directories("include")

add_library(${PROJECT_NAME} SHARED ${SOURCES})

set_target_properties(
	${PROJECT_NAME} PROPERTIES

	OUTPUT_NAME "gmcl_zxcmodule_win64"
	PREFIX ""
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-Os -s")
endif()

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Version: ${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
