project(message LANGUAGES CXX)

add_library(message SHARED message.cc folder.cc)
target_include_directories(message PUBLIC ${message_SOURCE_DIR})

add_executable(message_test message_test.cc)
target_link_libraries(message_test PRIVATE message)
