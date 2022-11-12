#define AVLTREEHELPER_H

#include "TreeNode.h"
#include "Direction.h"
#include "RotationType.h"

#include <stack>
#include <iostream>
#include <queue>

class AvlTreeHelper {
public:
    AvlTreeHelper();
    ~AvlTreeHelper();

    void levelPrint(TreeNode* cur);
    void dfs(TreeNode* cur);
    std::stack<std::pair<TreeNode*, Direction> > getPathStack(TreeNode* cur, int insertKey);
    bool isLeafNode(TreeNode* cur);
    void llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);
    void rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);
    TreeNode* rotateTree(RotationType, TreeNode* cur);
    void updateHeights(TreeNode* temp);
    int getBalanceFactor(TreeNode* temp);
    RotationType getRotationType(int balanceFactor, TreeNode* cur);
};