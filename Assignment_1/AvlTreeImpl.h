#define AVLTREEIMPL_H

#include "AvlTreeHelper.h"

#include <vector>
#include <queue>

class AvlTreeImpl {
private:
    TreeNode* root;
    AvlTreeHelper* avlTreeHelper;
    
    void updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction> >& pathStack, Direction direction);

public:
    AvlTreeImpl(AvlTreeHelper* avlTreeHelper);
    ~AvlTreeImpl();

    void insert(int key);
    void remove(int key);
    const Key* search(int key);
    const std::vector<const Key*> search(int low, int high);

    void print();
    void levelPrint();
};