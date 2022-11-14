#ifndef AVLTREEHELPER_H
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

    static void levelPrint(TreeNode* cur);
    static void dfs(TreeNode* cur);
    static std::stack<std::pair<TreeNode*, Direction> > getPathStack(TreeNode* cur, int insertKey);
    static bool isLeafNode(TreeNode* cur);
    static void llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);
    static void rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);
    static TreeNode* rotateTree(RotationType, TreeNode* cur);
    static void updateHeights(TreeNode* temp);
    static int getBalanceFactor(TreeNode* temp);
    static RotationType getRotationType(int balanceFactor, TreeNode* cur);
    static void getPrevHighest(std::stack<std::pair<TreeNode*, Direction> >& pathStack);
    static void getNextLowest(std::stack<std::pair<TreeNode*, Direction> >& pathStack);
};

#endif