cmake_minimum_required(VERSION 3.7.1)

project(redis-debug)

# aux_source_directory(../redis-6.0.3/src SOURCE_FILES)

MESSAGE( STATUS "CMAKE_SOURCE_DIR: " ${SOURCE_FILES}) 

set(SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/main.c
    ../redis-6.0.3/src/sds.c
    ../redis-6.0.3/src/zmalloc.c)

include_directories(../redis-6.0.3/src)

#sdsnewlen
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSDSNEWLEN")
#sdscatlen
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSDSCATLEN")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DDEBUG=1 -g -UUSE_STDIO -D__GCC_POSIX__=1 -W -O2")

MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )

add_executable(redis-debug ${SOURCE_FILES})