cmake_minimum_required(VERSION 3.21)

project(snake C)

set(CMAKE_C_STANDARD 99)

set(SOURCES 
	src/particles.c
	src/snake.c
	src/food.c
	src/main.c
)

set(HEADERS
	include/consts.h
	include/particles.h
	include/snake.h
	include/food.h
)

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# raylib library
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games
FetchContent_Declare(raylib GIT_REPOSITORY https://github.com/raysan5/raylib.git GIT_TAG master)
FetchContent_MakeAvailable(raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${raylib_SOURCE_DIR}/src/extras)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Options
target_compile_options(${PROJECT_NAME} PRIVATE $<$<CONFIG:Release>:-DDEBUG>)