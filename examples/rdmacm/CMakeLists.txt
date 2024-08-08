# Shared example files
find_package(Threads REQUIRED)

add_library(rdmacm_tools STATIC common.c)
target_link_libraries(rdmacm_tools PRIVATE rdmacm Threads::Threads)

add_executable(cmtime cmtime.c)
target_link_libraries(cmtime PRIVATE rdmacm rdmacm_tools)

#rdma_executable(mckey mckey.c)
#target_link_libraries(mckey LINK_PRIVATE rdmacm ${CMAKE_THREAD_LIBS_INIT} rdmacm_tools)

#rdma_executable(rcopy rcopy.c)
#target_link_libraries(rcopy LINK_PRIVATE rdmacm rdmacm_tools)

add_executable(rdma_client rdma_client.c)
target_link_libraries(rdma_client PRIVATE rdmacm)

add_executable(rdma_server rdma_server.c)
target_link_libraries(rdma_server PRIVATE rdmacm)

add_executable(rdma_xclient rdma_xclient.c)
target_link_libraries(rdma_xclient PRIVATE rdmacm)

add_executable(rdma_xserver rdma_xserver.c)
target_link_libraries(rdma_xserver PRIVATE rdmacm)

#rdma_executable(riostream riostream.c)
#target_link_libraries(riostream LINK_PRIVATE rdmacm rdmacm_tools)

add_executable(rping rping.c)
target_link_libraries(rping PRIVATE rdmacm Threads::Threads rdmacm_tools)

#rdma_executable(rstream rstream.c)
#target_link_libraries(rstream LINK_PRIVATE rdmacm rdmacm_tools)

add_executable(ucmatose cmatose.c)
target_link_libraries(ucmatose PRIVATE rdmacm rdmacm_tools)

#rdma_executable(udaddy udaddy.c)
#target_link_libraries(udaddy LINK_PRIVATE rdmacm rdmacm_tools)

#rdma_executable(udpong udpong.c)
#target_link_libraries(udpong LINK_PRIVATE rdmacm rdmacm_tools)
