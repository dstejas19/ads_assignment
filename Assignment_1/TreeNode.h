#define TREENODE_H

#include "Key.h"

class TreeNode {
private:
    Key* data;
    int leftHeight;
    int rightHeight;

    TreeNode* left;
    TreeNode* right;

public:
    TreeNode();
    TreeNode(Key* _data, TreeNode* _left, TreeNode* _right);
    ~TreeNode();

    Key* getData();
    int getLeftHeight();
    int getRightHeight();
    int getHeight();
    TreeNode* getLeft();
    TreeNode* getRight();

    void setData(int _data);
    void setLeftHeight(int _leftHeight);
    void setRightHeight(int _rightHeight);
    void setLeft(TreeNode* _left);
    void setRight(TreeNode* _right);
};