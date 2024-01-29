#include <iostream>
#include <hiredis.h>
#include <spdlog/spdlog.h>
#include <gtest/gtest.h>

class HiredisTest : public testing::Test {
 public:
  static const constexpr char *host = "127.0.0.1";
  static const constexpr uint32_t port = 6379u;
};

TEST_F(HiredisTest, ping) {
  auto *connect = redisConnect(host, port);
  if (!connect || connect->err) {
    spdlog::info("Connection error: {}\n", connect ? connect->errstr : "connection is null!");
    FAIL();
  }

  auto *reply = reinterpret_cast<redisReply *>(redisCommand(connect, "PING"));
  spdlog::info("{}", reply->type);
  spdlog::info("PING: {}", reply->str);

  freeReplyObject(reply);
  redisFree(connect);

  SUCCEED();
}

TEST_F(HiredisTest, pong) {
  auto *connect = redisConnect(host, port);
  if (!connect || connect->err) {
    spdlog::info("Connection error: {}\n", connect ? connect->errstr : "connection is null!");
    FAIL();
  }

  auto *reply = reinterpret_cast<redisReply *>(redisCommand(connect, "PING"));
  spdlog::info("{}", reply->type);
  spdlog::info("PING: {}", reply->str);

  freeReplyObject(reply);
  redisFree(connect);

  SUCCEED();
}
