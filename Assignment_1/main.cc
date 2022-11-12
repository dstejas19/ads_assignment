#include "AvlTree.h"
 
// Driver Code
int main()
{
    AvlTree *avlTree = new AvlTree();

    std::cout<<"New Tree Initialized"<<std::endl;

    // avlTree->insert(1);
    // avlTree->insert(3);
    // avlTree->insert(7);
    // avlTree->insert(6);
    // avlTree->insert(4);
    // avlTree->insert(5);
    // avlTree->insert(2);

    avlTree->insert(10);
    avlTree->insert(7);
    avlTree->insert(3);
    avlTree->insert(3);
    avlTree->insert(5);
    avlTree->insert(4);
    avlTree->insert(4);
    avlTree->insert(2);
    avlTree->insert(12);
    avlTree->insert(16);
    avlTree->insert(13);
    avlTree->insert(19);
    avlTree->insert(22);
    avlTree->insert(25);
    avlTree->insert(17);

    avlTree->print();

    std::cout<<"Search starts"<<std::endl;

    std::cout<<avlTree->search(5)->data<<std::endl;

    const std::vector<const Key*> keys = avlTree->search(10, 23);

    for(auto &a:keys) {
        std::cout<<a->data<<std::endl;
    }

    return 0;
}