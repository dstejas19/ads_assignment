#include "AvlTree.h"
 
// Driver Code
int main()
{
    AvlTree *avlTree = new AvlTree();

    avlTree->insert(1);
    avlTree->insert(3);
    avlTree->insert(7);
    avlTree->insert(6);
    avlTree->insert(4);
    avlTree->insert(5);
    avlTree->insert(2);

    avlTree->print();

    return 0;
}