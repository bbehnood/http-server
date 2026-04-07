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

add_compile_definitions(DEBUG_MODE)

target_compile_options(http_server PRIVATE -Wall -Wextra -Wpedantic)
