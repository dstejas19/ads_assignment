#ifndef AVLTREEIMPL_H
#define AVLTREEIMPL_H

#include "AvlTreeHelper.h"

#include <vector>

class AvlTreeImpl {
private:
    TreeNode* root;
    // AvlTreeHelper* avlTreeHelper;
    
    AvlTreeImpl();
    void updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction> >& pathStack, Direction direction);

public:
    ~AvlTreeImpl();

    static AvlTreeImpl* initialise();
    void insert(int key);
    void remove(int key);
    const Key* search(int key);
    const std::vector<const Key*> search(int low, int high);

    void print();
    void levelPrint();
};

#endif