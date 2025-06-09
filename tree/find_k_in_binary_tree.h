#include <iostream>

// 标题
// 二叉搜索树中的第K小的元素

// 题目描述
// 给定二叉搜索树，求所有元素中第k小的。k<=节点总数
struct TreeNode {
  int val;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode(int val) : val(val){};
};
class BinaryTree {
public:
  BinaryTree(){};
  int findKthSmallest(TreeNode *node, int &k);
  void preOrderTraversal(TreeNode *node);

  void inOrderTraversal(TreeNode *node);

  void postOrderTraversal(TreeNode *node);

private:
};
