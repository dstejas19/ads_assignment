#define AVLTREE_H

#include "TreeNode.h"
#include "RotationType.h"
#include "Direction.h"
#include <stack>
#include <vector>

class AvlTree {
private:
    TreeNode* root;

    std::stack<std::pair<TreeNode*, Direction>> getPathStack();
    void updateHeights(TreeNode* temp);
    int getBalanceFactor(TreeNode* temp);
    RotationType getRotationType(int balanceFactor, TreeNode* cur);
    void rotateTree(RotationType, TreeNode* cur);
    void updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction>>& pathStack);

    void llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);
    void rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p);

public:
    AvlTree();
    ~AvlTree();

    void insert(int key);
    void remove(int key);
    const Key* search(int key);
    const std::vector<const Key*> search(int low, int high);
};