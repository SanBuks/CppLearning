project(ch01_basic)

add_executable(ch01_basic redis.cc)
target_link_libraries(ch01_basic
  GTest::Main
  spdlog::spdlog
  hiredis::hiredis
)
copy_dll(ch01_basic
  GTest::GTest
  GTest::Main
  spdlog::spdlog
  hiredis::hiredis
)
