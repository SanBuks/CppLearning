project(ch02_async)

add_executable(a_async_basic        a_async_basic.cc)
target_link_libraries(a_async_basic ws2_32)

add_executable(b_async_client        b_async_client.cc)
target_link_libraries(b_async_client ws2_32)
add_executable(b_async_server        b_async_server.cc)
target_link_libraries(b_async_server ws2_32)


