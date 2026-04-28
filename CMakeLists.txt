cmake_minimum_required(VERSION 3.16)

project(http_server LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(http_server
	src/main.c
	src/server.c
	src/http.c
	src/utils.c
)

if (DEBUG_MODE STREQUAL "ON" OR DEBUG_MODE STREQUAL "TRUE")
    message(STATUS "Debug mode enabled.")
    add_compile_definitions(DEBUG_MODE)
    target_compile_options(http_server PRIVATE
		-g
		-O0
		-Wall -Wextra -Wpedantic
	)
else()
    message(STATUS "Debug mode disabled. Release mode enabled.")
    target_compile_options(http_server PRIVATE
		-O3
		-march=native
		-DNDEBUG
		-Wall -Wextra -Wpedantic
	)
endif()
