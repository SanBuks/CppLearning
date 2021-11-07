#include "folder.h"

#include <iostream>

Folder::Folder(std::string folder_name)
    : folder_name_(std::move(folder_name)) {}
Folder::Folder(const Folder &folder)
  : folder_name_(folder.folder_name_), messages_(folder.messages_) {
  if (!InitMessageConnection()) {
    throw std::runtime_error("Init Message Connection Failure");
  }
}
Folder& Folder::operator=(const Folder &folder) {
  if (this == &folder) {
    return *this;
  }
  using std::swap;
  Folder temp(folder);
  swap(*this, temp);
  return *this;
}
Folder::~Folder() {
  RemoveAllMessageConnections();
}

void Folder::set_folder_name(std::string folder_name) {
  folder_name_ = std::move(folder_name);
}

// 增加指定 Message 关联
bool Folder::AddMessageConnection(Message *p_message) {
  bool folder_insert_status;
  bool message_insert_status;

  folder_insert_status = p_message->Insert(this);
  if (!folder_insert_status) {
    goto folder_insert_roll_back;
  }

  message_insert_status = Insert(p_message);
  if (!message_insert_status) {
    goto message_insert_roll_back;
  }
  return true;

folder_insert_roll_back:
  return false;
message_insert_roll_back:
  p_message->Erase(this);
  return false;
}

// 初始化现有 Message 关联
bool Folder::InitMessageConnection() {
  bool folder_insert_status;

  for (auto message : messages_) {
    if (!(folder_insert_status = message->Insert(this))) {
      break;
    }
  }
  if (!folder_insert_status) {
    goto folder_insert_roll_back;
  }
  return true;

folder_insert_roll_back:
  for (auto message : messages_) {
    message->Erase(this);
  }
  return false;
}

// 删除指定 Message 关联
void Folder::RemoveMessageConnection(Message *p_message) {
  p_message->Erase(this);
  messages_.erase(p_message);
}

// 删除所有 Message 关联
void Folder::RemoveAllMessageConnections() {
  while (!messages_.empty()) {
    RemoveMessageConnection(*messages_.begin());
  }
  Clear();
}

void Folder::Print() {
  std::cout << folder_name_ << " has " << messages_.size() << " msgs : \n";
  std::cout << "Msgs Stored in Folders are [\n";
  for (auto msg : messages_) {
    std::cout << msg->Abstract() << "\n";
  }
  std::cout << "]\n";
}

bool Folder::Insert(Message *p_message) {
  if (messages_.find(p_message) != messages_.end()) {
    return true;
  } else {
    return messages_.insert(p_message).second;
  }
}

void Folder::Erase(Message *p_message) {
  messages_.erase(p_message);
}

void Folder::Clear() {
  messages_.clear();
}

void swap(Folder &lhs, Folder &rhs) noexcept {
  using std::swap;
  swap(lhs.folder_name_, rhs.folder_name_);
}
