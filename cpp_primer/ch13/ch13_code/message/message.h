#ifndef CPP_PRIMER_CH13_CODE_MESSAGE_H_
#define CPP_PRIMER_CH13_CODE_MESSAGE_H_

#include <string>
#include <set>
#include <utility>

// Folder 多对多 Message
// Folder 可以独立于 Message 存在, 反之亦然, 所以二者没有 资源管理的关系
// Folder 与 Message 之间通过 指针集合相关联即可
class Folder;

class Message {

  friend class Folder;
  friend void swap(Message &lhs, Message &rhs) noexcept;

 public:
  explicit Message(std::string str = "");
  Message(const Message &m);
  Message(Message &&m);
  Message &operator=(const Message &rhs);
  Message &operator=(Message &&rhs);
  ~Message();

  std::string Abstract() const;
  void set_contents(std::string contents);
  const std::string &contents() const  { return contents_; }

  // 增加指定 Folder 关联 (对 OOM 保证强异常安全)
  bool AddFolderConnection(Folder *p_folder);
  // 初始化现有 Folder 关联 (对 OOM 保证强异常安全)
  bool InitFolderConnection();
  // 移动初始化现有 Folder 关联 (对 OOM 保证强异常安全)
  bool MoveInitFolderConnection(Message *move_target);
  // 删除指定 Folder 关联
  void RemoveFolderConnection(Folder *p_folder);
  // 删除所有 Folder 关联
  void RemoveAllFolderConnections();
  // 打印 信息
  void Print();

 private:
  // folders_ 基本增删操作
  bool Insert(Folder *p_folder);
  void Erase(Folder *p_folder);
  void Clear();

  std::string contents_;
  std::set<Folder *> folders_;
};

void swap(Message &lhs, Message &rhs) noexcept;

#endif
