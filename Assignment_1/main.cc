#include "AvlTree.h"
 
// Driver Code

void print(const Key* key) {
    std::cout<<key->data<<std::endl;
}

void print(const std::vector<const Key*> keys) {
    for(auto &a:keys) {
        std::cout<<a->data<<std::endl;
    }
}

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

    print(avlTree->search(5));
    print(avlTree->search(-3));
    print(avlTree->search(100));
    print(avlTree->search(8));

    std::cout<<"Search with bounds starts"<<std::endl;

    print(avlTree->search(10, 23));

    print(avlTree->search(-5, 1));

    print(avlTree->search(100, 1011));

    return 0;
}