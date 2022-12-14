#include "Tree/AvlTreeImpl.h"
 
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
    AvlTreeImpl *avlTree = AvlTreeImpl::initialize();

    std::cout<<"New Tree Initialized"<<std::endl;

    // avlTree->insert(1);
    // avlTree->insert(3);
    // avlTree->insert(7);
    // avlTree->insert(6);
    // avlTree->insert(4);
    // avlTree->insert(5);
    // avlTree->insert(2);

    // avlTree->remove(6);
    // avlTree->remove(7);
    // avlTree->remove(5);

    // avlTree->print();
    // avlTree->levelPrint();

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
    // avlTree->insert(14);

    // // avlTree->remove(22);
    // avlTree->remove(17); //LR
    // avlTree->remove(3); 
    // avlTree->remove(2); //RR
    // avlTree->remove(22);
    // avlTree->remove(25); //LL
    // avlTree->remove(13); //RL

    // avlTree->print();
    // avlTree->levelPrint();
    
    

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


    avlTree->insert(21);
    avlTree->insert(108);
    // avlTree->insert(5);
    // avlTree->insert(1897);
    // avlTree->insert(4325);
    // avlTree->remove(108);
    // print(avlTree->search(1897));
    // avlTree->insert(102);
    // avlTree->insert(65);
    // avlTree->remove(102);
    // avlTree->remove(21);
    // avlTree->insert(106);
    // avlTree->insert(23);
    // print(avlTree->search(23, 99));
    // avlTree->insert(32);
    // avlTree->insert(220);
    // print(avlTree->search(33));
    // print(avlTree->search(21));
    // avlTree->remove(4325);
    print(avlTree->search(5));

    return 0;
}