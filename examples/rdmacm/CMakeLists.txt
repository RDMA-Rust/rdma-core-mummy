# Shared example files
find_package(Threads REQUIRED)

add_library(rdmacm_tools STATIC common.c)
target_link_libraries(rdmacm_tools PRIVATE rdmacm Threads::Threads)

add_executable(cmtime cmtime.c)
target_link_libraries(cmtime PRIVATE rdmacm rdmacm_tools)

add_executable(mckey mckey.c)
target_link_libraries(mckey PRIVATE rdmacm Threads::Threads rdmacm_tools)

add_executable(rdma_client rdma_client.c)
target_link_libraries(rdma_client PRIVATE rdmacm)

add_executable(rdma_server rdma_server.c)
target_link_libraries(rdma_server PRIVATE rdmacm)

add_executable(rdma_xclient rdma_xclient.c)
target_link_libraries(rdma_xclient PRIVATE rdmacm)

add_executable(rdma_xserver rdma_xserver.c)
target_link_libraries(rdma_xserver PRIVATE rdmacm)

add_executable(rping rping.c)
target_link_libraries(rping PRIVATE rdmacm Threads::Threads rdmacm_tools)

add_executable(ucmatose cmatose.c)
target_link_libraries(ucmatose PRIVATE rdmacm rdmacm_tools)

add_executable(udaddy udaddy.c)
target_link_libraries(udaddy PRIVATE rdmacm rdmacm_tools)
