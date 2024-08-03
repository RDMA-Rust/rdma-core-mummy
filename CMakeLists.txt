cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(rdma-core-mummy C)

add_library(ibverbs STATIC
    src/ibverbs.c
)

target_include_directories(ibverbs
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
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
)

target_link_libraries(rdmacm
    PRIVATE
        ${CMAKE_DL_LIBS}
)
