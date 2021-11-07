#include "tree.h"

#include <string>

TreeNode::TreeNode(std::string &&value, TNP left , TNP right)
    : value_(value), left_(left), right_(right), count_(0) {};

TreeNode::TNUP *TreeNode::InitLc(std::string &&value) {
  auto p = new TreeNode(std::move(value));
  left_.reset(p);
  ++count_;
  return &left_;
}

TreeNode::TNUP *TreeNode::InitRc(std::string &&value) {
  auto p = new TreeNode(std::move(value));
  right_.reset(p);
  ++count_;
  return &right_;
}

TreeNode::~TreeNode() {
  RemoveSubTree(std::move(left_));
  RemoveSubTree(std::move(right_));
}

void TreeNode::RemoveSubTree(TNUP sub_root) {
  while (sub_root->count_ > 0) {
    auto leaf = sub_root->left_ ? &sub_root->left_ : &sub_root->right_ ;
    auto count = &sub_root->count_;
    while ((*leaf)->count_ > 0) {
      count = &(*leaf)->count_;
      leaf = (*leaf)->left_ ? &(*leaf)->left_ : &(*leaf)->right_ ;
    }
    --*count;
    (*leaf).reset();
  }
}