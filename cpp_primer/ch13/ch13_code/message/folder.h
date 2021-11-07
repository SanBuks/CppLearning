#ifndef CPP_PRIMER_CH13_CODE_FOLDER_H_
#define CPP_PRIMER_CH13_CODE_FOLDER_H_

#include "message.h"

// Folder 多对多 Message
// Folder 可以独立于 Message 存在, 反之亦然, 所以二者没有 资源管理的关系
// Folder 与 Message 之间通过 指针集合相关联即可
class Folder {

  friend class Message;
  friend void swap(Folder &lhs, Folder &rhs) noexcept ;

 public:
  explicit Folder(std::string folder_name = "");
  Folder(const Folder &folder);
  Folder& operator=(const Folder &folder);
  ~Folder();

  void set_folder_name(std::string folder_name);
  const std::string &folder_name() const { return folder_name_; };

  // 增加指定 Message 关联 (对于 std::set 的 insert 操作 保证强异常安全)
  bool AddMessageConnection(Message *p_message);
  // 初始化现有 Message 关联 (对于 std::set 的 insert 操作 保证强异常安全)
  bool InitMessageConnection();
  // 删除指定 Message 关联
  void RemoveMessageConnection(Message *p_message);
  // 删除所有 Message 关联
  void RemoveAllMessageConnections();
  // 打印 信息
  void Print();

 private:
  // messages_ 基本增删操作
  bool Insert(Message *p_message);
  void Erase(Message *p_message);
  void Clear();

  std::string folder_name_;
  std::set<Message *> messages_;
};

void swap(Folder &lhs, Folder &rhs) noexcept;

#endif