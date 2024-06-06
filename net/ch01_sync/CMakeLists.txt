project(ch01_sync)

add_executable(a_sync_basic a_sync_basic.cc)
target_link_libraries(a_sync_basic PRIVATE asio spdlog::spdlog)

add_executable(b_sync_rw b_sync_rw.cc)
target_link_libraries(b_sync_rw PRIVATE asio spdlog::spdlog)

add_executable(c_sync_client c_sync_client.cc)
target_link_libraries(c_sync_client asio spdlog::spdlog Iconv::Iconv)

add_executable(c_sync_server c_sync_server.cc)
target_link_libraries(c_sync_server asio spdlog::spdlog)

