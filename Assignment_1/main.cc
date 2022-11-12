#include "AvlTree.h"
 
// Driver Code

void print(const Key* key) {
    if(!key) {
        std::cout<<"Not present"<<std::endl;
        return;
    }
    std::cout<<key->data<<std::endl;
}

void print(const std::vector<const Key*> keys) {
    if(keys.empty()) {
        std::cout<<"Not present"<<std::endl;
        return;
    }
    for(auto &a:keys) {
        std::cout<<a->data<<std::endl;
    }
}

int main()
{
    AvlTreeHelper *avlTreeHelper = new AvlTreeHelper();
    AvlTree *avlTree = new AvlTree(avlTreeHelper);

    std::cout<<"New Tree Initialized"<<std::endl;

    avlTree->insert(1);
    avlTree->insert(3);
    avlTree->insert(7);
    avlTree->insert(6);
    avlTree->insert(4);
    avlTree->insert(5);
    avlTree->insert(2);

    avlTree->remove(6);
    avlTree->remove(7);
    avlTree->remove(5);

    // avlTree->insert(10);
    // avlTree->insert(7);
    // avlTree->insert(3);
    // avlTree->insert(3);
    // avlTree->insert(5);
    // avlTree->insert(4);
    // avlTree->insert(4);
    // avlTree->insert(2);
    // avlTree->insert(12);
    // avlTree->insert(16);
    // avlTree->insert(13);
    // avlTree->insert(19);
    // avlTree->insert(22);
    // avlTree->insert(25);
    // avlTree->insert(17);

    avlTree->print();

    // std::cout<<"Search starts"<<std::endl;

    // print(avlTree->search(5));
    // print(avlTree->search(-3));
    // print(avlTree->search(100));
    // print(avlTree->search(8));
    // print(avlTree->search(10));
    // print(avlTree->search(7));
    // print(avlTree->search(3));
    // print(avlTree->search(5));
    // print(avlTree->search(4));
    // print(avlTree->search(2));
    // print(avlTree->search(12));
    // print(avlTree->search(16));
    // print(avlTree->search(13));
    // print(avlTree->search(19));
    // print(avlTree->search(22));
    // print(avlTree->search(25));
    // print(avlTree->search(17));

    // std::cout<<"Search with bounds starts"<<std::endl;

    // print(avlTree->search(10, 23));

    // print(avlTree->search(2, 25));

    // print(avlTree->search(5, 17));

    // print(avlTree->search(-5, 1));

    // print(avlTree->search(100, 1011));

    return 0;
}