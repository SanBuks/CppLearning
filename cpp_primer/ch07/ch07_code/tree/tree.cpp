#include "tree.h"
unsigned long TreeNode::size(){
    unsigned long size = 0;
    if(lchild) size = lchild->size();
    if(rchild) size += rchild->size();
    return size + 1;
};