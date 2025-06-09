#include "find_k_in_binary_tree.h"
#include <iostream>
void BinaryTree::postOrderTraversal(TreeNode *node) {
  // 左右根
  if (node == nullptr) {
    return;
  }
  postOrderTraversal(node->left);
  postOrderTraversal(node->right);
  std::cout << "val:" << node->val << std::endl;
}
void BinaryTree::inOrderTraversal(TreeNode *node) {
  if (node == nullptr) {
    return;
  }
  // 左根右
  inOrderTraversal(node->left);
  std::cout << "val:" << node->val << std::endl;
  inOrderTraversal(node->right);
}
void BinaryTree::preOrderTraversal(TreeNode *node) {
  // 根左右
  if (node == nullptr) {
    return;
  }
  std::cout << "val:" << node->val << std::endl;
  preOrderTraversal(node->left);
  preOrderTraversal(node->right);
}
int BinaryTree::findKthSmallest(TreeNode *node, int &k) {
  if (node == nullptr) {
    return -1;
  }

  int res = findKthSmallest(node->left, k);
  if (res != -1) {
    return res;
  }
  // 根，中序遍历
  if (--k == 0) {
    return node->val;
  }
  return findKthSmallest(node->right, k);
}

// 创建二叉搜索树的辅助函数
TreeNode *createBST() {
  TreeNode *root = new TreeNode(5);
  root->left = new TreeNode(3);
  root->right = new TreeNode(7);
  root->left->left = new TreeNode(2);
  root->left->right = new TreeNode(4);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(8);
  return root;
}

int main() {
  // 创建二叉搜索树
  TreeNode *root = createBST();
  BinaryTree tree;

  // 测试查找第k小的元素
  for (int k = 1; k <= 7; ++k) {
    int k_copy = k;
    int result = tree.findKthSmallest(root, k_copy);
    std::cout << "第 " << k << " 小的元素是: " << result << std::endl;
  }

  // 清理内存
  // 实际项目中应该实现树的析构函数
  delete root->right->right;
  delete root->right->left;
  delete root->left->right;
  delete root->left->left;
  delete root->right;
  delete root->left;
  delete root;

  return 0;
}