#include "AvlTreeImpl.h"

AvlTreeImpl :: AvlTreeImpl()  {
    // this->avlTreeHelper = avlTreeHelper;
}

AvlTreeImpl :: ~AvlTreeImpl()  {
    delete root;
}

AvlTreeImpl* AvlTreeImpl :: initialise() {
    // AvlTreeHelper* avlTreeHelper = new AvlTreeHelper();
    return new AvlTreeImpl();
}

const Key* AvlTreeImpl :: search(int key) {
    std::stack<TreeNode*> s;
    TreeNode* cur = this->root;
    TreeNode* prev;
    int count = 0;

    while(cur || !s.empty()) {
        do {
            if(!cur) {
                break;
            }
            s.push(cur);
            ++count;

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data > key);

        cur = s.top();
        s.pop();

        if(cur->getData()->data == key) {
            std::cout<<"The count for "<<key<<" is "<<count<<std::endl;
            return cur->getData();
        }
        else if(cur->getData()->data < key) {
            cur = cur->getRight();
        }
        else {
            cur = nullptr;
        }
    }

    return nullptr;
}

const std::vector<const Key*> AvlTreeImpl :: search(int low, int high) {
    std::vector<const Key*> keys;
    std::stack<TreeNode*> s;
    TreeNode* cur = this->root;
    TreeNode* prev;

    while(cur || !s.empty()) {
        do {
            if(!cur) {
                break;
            }
            s.push(cur);

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data > low);

        cur = s.top();
        s.pop();

        int key = cur->getData()->data;

        if(key >= low && key <= high) {
            keys.push_back(cur->getData());
        }

        if(key < high) {
            cur = cur->getRight();
        }
        else {
            cur = nullptr;
        }
    }

    return keys;
}

void AvlTreeImpl :: insert(int key) {
    std::cout<<"Inserting "<<key<<" into the tree"<<std::endl;
    std::stack<std::pair<TreeNode*, Direction> > pathStack = AvlTreeHelper::getPathStack(this->root, key);

    TreeNode* temp = new TreeNode(new Key(key), nullptr, nullptr);

    if(pathStack.empty()) {
        this->root = temp;
        return;
    }

    int leafValue = pathStack.top().first->getData()->data;

    if(leafValue == key) {
        std::cout<<"Key "<<key<<" is already present in the tree"<<std::endl;
        delete temp;
        return;
    }
    else if(leafValue > key) {
        std::cout<<"Inserting "<<key<<" to left of "<<leafValue<<std::endl;
        pathStack.top().first->setLeft(temp);
    }
    else {
        std::cout<<"Inserting "<<key<<" to right of "<<leafValue<<std::endl;
        pathStack.top().first->setRight(temp);
    }
    pathStack.pop();

    while(!pathStack.empty()) {
        TreeNode* cur = pathStack.top().first;
        Direction direction = pathStack.top().second;
        pathStack.pop();

        AvlTreeHelper::updateHeights(cur);

        int balanceFactor = AvlTreeHelper::getBalanceFactor(cur);
        if(balanceFactor == 0) {
            break;
        }
        else if(balanceFactor == 2 || balanceFactor == -2) {
            std::cout<<"Balancing has to be done. The balance factor is "<<balanceFactor<<std::endl;
            RotationType rotationType = AvlTreeHelper::getRotationType(balanceFactor, cur);
            cur = AvlTreeHelper::rotateTree(rotationType, cur);
            this->updateParent(cur, pathStack, direction);
            
            break;
        }
    }

    std::cout<<"Inserted "<<key<<" to the tree"<<std::endl;
    std::cout<<"Printing"<<std::endl;
    std::cout<<"---------"<<std::endl;
    this->levelPrint();
    std::cout<<"---------"<<std::endl;
}

void AvlTreeImpl :: remove(int key) {
    std::cout<<"Deleting "<<key<<" from the tree"<<std::endl;
    std::stack<std::pair<TreeNode*, Direction> > pathStack = AvlTreeHelper::getPathStack(this->root, key);

    TreeNode* toBeRemoved = pathStack.top().first;
    Direction toBeRemovedDirection = pathStack.top().second;

    if(!toBeRemoved || toBeRemoved->getData()->data != key) {
        std::cout<<"Key is not present"<<std::endl;

        return;
    }

    if(AvlTreeHelper::isLeafNode(toBeRemoved)) {
        pathStack.pop();
        updateParent(nullptr, pathStack, toBeRemovedDirection);

        delete toBeRemoved;
    }
    else {
        AvlTreeHelper::getPrevHighest(pathStack);

        if(pathStack.top().first == toBeRemoved) {
            AvlTreeHelper::getNextLowest(pathStack);
        }

        TreeNode* toBeReplaced = pathStack.top().first;
        Direction replacedDirection = pathStack.top().second;
        pathStack.pop();

        toBeRemoved->setData(toBeReplaced->getData()->data);

        updateParent(nullptr, pathStack, replacedDirection);

        delete toBeReplaced;
    }

    while(!pathStack.empty()) {
        TreeNode* cur = pathStack.top().first;
        Direction direction = pathStack.top().second;
        pathStack.pop();

        AvlTreeHelper::updateHeights(cur);

        int balanceFactor = AvlTreeHelper::getBalanceFactor(cur);
        if(balanceFactor == 1 || balanceFactor == -1) {
            break;
        }
        else if(balanceFactor == 2 || balanceFactor == -2) {
            std::cout<<"Balancing has to be done. The balance factor is "<<balanceFactor<<std::endl;
            RotationType rotationType = AvlTreeHelper::getRotationType(balanceFactor, cur);
            cur = AvlTreeHelper::rotateTree(rotationType, cur);
            this->updateParent(cur, pathStack, direction);
        }
    }

    std::cout<<"Deleted "<<key<<" from the tree"<<std::endl;
}

void AvlTreeImpl :: updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction> >& pathStack, Direction direction) {
    if(pathStack.empty()) {
        this->root = cur;

        return;
    }

    if(direction == L) {
        pathStack.top().first->setLeft(cur);
    }
    else {
        pathStack.top().first->setRight(cur);
    }
}

void AvlTreeImpl :: print() {
    AvlTreeHelper::dfs(this->root);
}

void AvlTreeImpl :: levelPrint() {
    AvlTreeHelper::levelPrint(this->root);
}