#include "TreeNode.h"

TreeNode :: TreeNode() {
}

TreeNode :: ~TreeNode() {
    delete data;
    delete left;
    delete right;
}

TreeNode :: TreeNode(Key* _data, TreeNode* _left, TreeNode* _right) {
    this->data = _data;
    this->left = _left;
    this->right = _right;
    this->leftHeight = 0;
    this->rightHeight = 0;
}

Key* TreeNode :: getData() {
    return this->data;
}

int TreeNode :: getLeftHeight() {
    return this->leftHeight;
}

int TreeNode :: getRightHeight() {
    return this->rightHeight;
}

TreeNode* TreeNode :: getLeft() {
    return this->left; 
}

TreeNode* TreeNode :: getRight() {
    return this->right;
}

int TreeNode :: getHeight() {
    return this->leftHeight >= this->rightHeight ? leftHeight : rightHeight;
}

void TreeNode :: setData(int _data) {
    this->data->data = _data;
}

void TreeNode :: setLeftHeight(int _leftHeight) {
    this->leftHeight = _leftHeight;
}

void TreeNode :: setRightHeight(int _rightHeight) {
    this->rightHeight = _rightHeight;
}

void TreeNode :: setLeft(TreeNode* _left) {
    this->left = _left;
    if(_left) {
        this->leftHeight = _left->getLeftHeight() + 1;
    }
    else {
        this->leftHeight = 0;
    }
}

void TreeNode :: setRight(TreeNode* _right) {
    this->right = _right;
    if(_right) {
        this->rightHeight = _right->getRightHeight() + 1;
    }
    else {
        this->rightHeight = 0;
    }
}