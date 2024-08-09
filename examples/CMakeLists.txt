add_executable(hello_ibverbs hello_ibverbs.c)

target_link_libraries(hello_ibverbs PRIVATE ibverbs)

add_subdirectory(ibverbs)
add_subdirectory(rdmacm)
