#define TREENODE_H

class TreeNode {
private:
    int data;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode();
    TreeNode(int _data, TreeNode* _left, TreeNode* _right);
    ~TreeNode();
};