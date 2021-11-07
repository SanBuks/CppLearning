#include "message.h"

#include <iostream>
#include <stdexcept>

#include "folder.h"

Message::Message(std::string contents)
    : contents_(std::move(contents)) {}
Message::Message(const Message &message)
    : contents_(message.contents_), folders_(message.folders_) {
  if (!InitFolderConnection()) {
    throw std::runtime_error("Init Folder Connection Failure");
  }
}
Message::Message(Message &&message)
    : contents_(std::move(message.contents_)),
      folders_(std::move(message.folders_)) {
  if (!MoveInitFolderConnection(&message)) {
    throw std::runtime_error("Move Init Folder Connection Failure");
  }
}
Message &Message::operator=(const Message &rhs) {
  if (this == &rhs) {
    return *this;
  }
  using std::swap;
  Message temp(rhs);
  swap(*this, temp);
  return *this;
}
Message &Message::operator=(Message &&rhs) {
  auto move_target = &rhs;
  if (this == &rhs) {
    return *this;
  }
  bool message_insert_status;
  for (auto folder : rhs.folders_) {
    if (!(message_insert_status = folder->Insert(this))) {
      break;
    }
  }
  if (!message_insert_status) {
    goto message_insert_roll_back;
  }
  for (auto folder : rhs.folders_) {
    folder->Erase(move_target);
  }
  contents_ = std::move(rhs.contents_);
  folders_ = std::move(rhs.folders_);
  return *this;

message_insert_roll_back:
  for (auto folder : folders_) {
    folder->Erase(this);
  }
  throw std::runtime_error("Move Init Folder Connection Failure");
}
Message::~Message() {
  RemoveAllFolderConnections();
}

void Message::set_contents(std::string contents) {
  contents_ = std::move(contents);
}
std::string Message::Abstract() const {
  return contents_.substr(0, 8);
}

bool Message::AddFolderConnection(Folder *p_folder) {
  bool message_insert_status;
  bool folder_insert_status;

  message_insert_status = p_folder->Insert(this);
  if (!message_insert_status) {
    goto message_insert_roll_back;
  }

  folder_insert_status = Insert(p_folder);
  if (!folder_insert_status) {
    goto folder_insert_roll_back;
  }
  return true;

message_insert_roll_back:
  return false;
folder_insert_roll_back:
  p_folder->Erase(this);
  return false;
}

bool Message::InitFolderConnection() {
  bool message_insert_status;

  for (auto folder : folders_) {
    if (!(message_insert_status = folder->Insert(this))) {
      break;
    }
  }
  if (!message_insert_status) {
    goto message_insert_roll_back;
  }
  return true;

message_insert_roll_back:
  for (auto folder : folders_) {
    folder->Erase(this);
  }
  return false;
}

bool Message::MoveInitFolderConnection(Message *move_target) {
  bool message_insert_status;
  for (auto folder : folders_) {
    if (!(message_insert_status = folder->Insert(this))) {
      break;
    }
  }
  if (!message_insert_status) {
    goto message_insert_roll_back;
  }
  for (auto folder : folders_) {
    folder->Erase(move_target);
  }
  return true;
message_insert_roll_back:
  for (auto folder : folders_) {
    folder->Erase(this);
  }
  return false;
}

void Message::RemoveFolderConnection(Folder *p_folder) {
  p_folder->Erase(this);
  folders_.erase(p_folder);
}

void Message::RemoveAllFolderConnections() {
  while(!folders_.empty()) {
    RemoveFolderConnection(*folders_.begin());
  }
  Clear();
}

void Message::Print() {
  std::cout << Abstract() << "\n";
  std::cout << "Stored in Folders [";
  if (!folders_.empty()) {
    auto it = folders_.begin();
    std::cout << (*it++)->folder_name();
    while (it != folders_.end()) {
      std::cout << ", " << (*it++)->folder_name();
    }
  }
  std::cout << "]\n";
}

bool Message::Insert(Folder *p_folder) {
  if (folders_.find(p_folder) != folders_.end()) {
    return true;
  } else {
    return folders_.insert(p_folder).second;
  }
}

void Message::Erase(Folder *p_folder) {
  folders_.erase(p_folder);
}

void Message::Clear() {
  folders_.clear();
}

void swap(Message &lhs, Message &rhs) noexcept {
  using std::swap;
  swap(lhs.contents_, rhs.contents_);
}