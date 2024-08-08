cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(rdma-core-mummy C)

option(BUILD_EXAMPLES "build examples for ibverbs and rdmacm" OFF)

add_library(ibverbs STATIC
    src/ibverbs.c
)

target_include_directories(ibverbs
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(ibverbs
    PRIVATE
        ${CMAKE_DL_LIBS}
)

add_library(rdmacm STATIC
    src/rdmacm.c
)

target_include_directories(rdmacm
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(rdmacm
    PRIVATE
        ${CMAKE_DL_LIBS}
)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)
