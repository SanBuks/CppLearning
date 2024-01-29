include(FetchContent)

#------------------- GTest 单元测试 -------------------#
if (EXISTS ${CMAKE_SOURCE_DIR}/thirdparty/googletest)
  set(repo_googletest "file://${CMAKE_SOURCE_DIR}/thirdparty/googletest")
else ()
  set(repo_googletest "git@github.com:google/googletest.git")
endif ()

#set(FETCHCONTENT_SOURCE_DIR_googletest "${CMAKE_SOURCE_DIR}/thirdparty/gtest")
FetchContent_Declare(
  googletest
  GIT_REPOSITORY ${repo_googletest}
  GIT_TAG        v1.14.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE INTERNAL "")
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest ALIAS gtest)
add_library(GTest::Main  ALIAS gtest_main)
include(GoogleTest)

#------------------- Hiredis redis 通讯 -------------------#
if (EXISTS ${CMAKE_SOURCE_DIR}/thirdparty/hiredis)
  set(repo_hiredis "file://${CMAKE_SOURCE_DIR}/thirdparty/hiredis")
else ()
  set(repo_hiredis "git@github.com:redis/hiredis.git")
endif ()
set(FETCHCONTENT_SOURCE_DIR_hiredis "${CMAKE_SOURCE_DIR}/thirdparty/hiredis")
FetchContent_Declare(
  hiredis
  GIT_REPOSITORY ${repo_hiredis}
  GIT_TAG        v1.2.0
)
FetchContent_MakeAvailable(hiredis)

#------------------- spdlog 日志 -------------------#
if (EXISTS ${CMAKE_SOURCE_DIR}/thirdparty/spdlog)
  set(repo_spdlog "file://${CMAKE_SOURCE_DIR}/thirdparty/spdlog")
else ()
  set(repo_spdlog "git@github.com:gabime/spdlog.git")
endif ()
set(FETCHCONTENT_SOURCE_DIR_spdlog "${CMAKE_SOURCE_DIR}/thirdparty/spdlog")
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY ${repo_spdlog}
  GIT_TAG        v1.13.0
)
set(SPDLOG_BUILD_SHARED OFF CACHE BOOL "Build spdlog as a shared library")
FetchContent_MakeAvailable(spdlog)