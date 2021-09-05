class Tree;

class TreeNode{
    friend class Tree;
public:
    TreeNode(int val = 0) : data(val), parent(nullptr), lchild(nullptr), rchild(nullptr){}
    unsigned long size();
private:
    int data;
    TreeNode *lchild;
    TreeNode *rchild;
    TreeNode *parent;
};

class Tree{
public:
    Tree() : root(nullptr), size(0){}
    Tree(TreeNode *p) : root(p), size(p->size()) {}
private:
    TreeNode *root;
    unsigned long size;
};