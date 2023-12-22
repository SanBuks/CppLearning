project(ch01_sync)

add_executable(a_sync_basic        a_sync_basic.cc)
target_link_libraries(a_sync_basic ws2_32)

add_executable(b_sync_client        b_sync_client.cc)
target_link_libraries(b_sync_client ws2_32)
add_executable(b_sync_server        b_sync_server.cc)
target_link_libraries(b_sync_server ws2_32)
