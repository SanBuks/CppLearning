#ifndef CH13_CH13_CH13_CODE_TREE_TREE_H_
#define CH13_CH13_CH13_CODE_TREE_TREE_H_

#include <string>
#include <memory>

class BinStrTree;
class TreeNode {
  friend class BinStrTree;
 public:
  typedef TreeNode *TNP;
  typedef std::unique_ptr<TreeNode> TNUP;

  explicit TreeNode(std::string &&value = std::string(),
                    TNP left = nullptr, TNP right = nullptr);
  TreeNode(const TreeNode &tree_node) = delete;
  TreeNode &operator=(const TreeNode &rhs) = delete;
  ~TreeNode();

  TNUP *InitLc(std::string &&value);
  TNUP *InitRc(std::string &&value);
  void RemoveSubTree(TNUP sub_root);

 private:
  std::string value_;
  int count_;  // 真孩子个数
  TNUP left_;
  TNUP right_;
};

class BinStrTree {
 public:
  typedef TreeNode *TNP;
  typedef std::unique_ptr<TreeNode> TNUP;

  explicit BinStrTree();
  BinStrTree(const BinStrTree &tree_node) = delete;
  BinStrTree &operator=(const BinStrTree &rhs) = delete;
  ~BinStrTree();

 private:

  TNUP root;
};

#endif
