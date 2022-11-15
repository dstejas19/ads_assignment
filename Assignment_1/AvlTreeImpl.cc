#include "AvlTreeImpl.h"

AvlTreeImpl :: AvlTreeImpl()  {
}

AvlTreeImpl :: ~AvlTreeImpl()  {
    delete root;
}

AvlTreeImpl* AvlTreeImpl :: initialize() {
    return new AvlTreeImpl();
}

// search for key, return key if present else return null
const Key* AvlTreeImpl :: search(int key) {
    std::cout<<"Searching for "<<key<<" in the tree"<<std::endl;
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
        } while(cur && prev->getData()->data > key);

        cur = s.top();
        s.pop();

        if(cur->getData()->data == key) {
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
    std::cout<<"Searching for keys between "<<low<<" and "<<high<<" in the tree"<<std::endl;
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

    // create a node to insert
    TreeNode* temp = new TreeNode(new Key(key), nullptr, nullptr);

    // empty patchstack denotes empty tree
    if(pathStack.empty()) {
        this->root = temp;
        return;
    }

    int leafValue = pathStack.top().first->getData()->data;

    // if it is already present in the tree, delete the newly created node
    // if the leaf value is greater than key, insert new node to it's left
    // if the leaf value is greater than key, insert new node to it's right
    if(leafValue == key) {
        delete temp;
        return;
    }
    else if(leafValue > key) {
        pathStack.top().first->setLeft(temp);
    }
    else {
        pathStack.top().first->setRight(temp);
    }
    pathStack.pop();

    //keep going up the root, update the heights and make sure balance factor lies between -1 and 1, otherwise rotate and break. If balance factor is 0, break from loop
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
            // rotate tree and mkae necessary structural changes
            RotationType rotationType = AvlTreeHelper::getRotationType(balanceFactor, cur);
            cur = AvlTreeHelper::rotateTree(rotationType, cur);
            this->updateParent(cur, pathStack, direction);
            
            break;
        }
    }
}

void AvlTreeImpl :: remove(int key) {
    std::cout<<"Deleting "<<key<<" from the tree"<<std::endl;
    std::stack<std::pair<TreeNode*, Direction> > pathStack = AvlTreeHelper::getPathStack(this->root, key);

    TreeNode* toBeRemoved = pathStack.top().first;
    Direction toBeRemovedDirection = pathStack.top().second;

    // if not present, stop
    if(!toBeRemoved || toBeRemoved->getData()->data != key) {
        return;
    }

    // if it is a leaf node, delete it
    if(AvlTreeHelper::isLeafNode(toBeRemoved)) {
        pathStack.pop();
        updateParent(nullptr, pathStack, toBeRemovedDirection);

        delete toBeRemoved;
    }
    else { // else, replace it with previous highest or next lowest
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

    // check for balance factor in the tree
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
            RotationType rotationType = AvlTreeHelper::getRotationType(balanceFactor, cur);
            cur = AvlTreeHelper::rotateTree(rotationType, cur);
            this->updateParent(cur, pathStack, direction);
        }
    }
}

// update the top-most node in the stack
void AvlTreeImpl :: updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction> >& pathStack, Direction direction) {
    // if emoty, set cur as root
    if(pathStack.empty()) {
        this->root = cur;

        return;
    }

    // if Lm set top-most node's left subtree as cur
    if(direction == L) {
        pathStack.top().first->setLeft(cur);
    }
    else {
        pathStack.top().first->setRight(cur); // set topmost node's right subtree as cur
    }
}

void AvlTreeImpl :: print() {
    AvlTreeHelper::dfs(this->root);
}

void AvlTreeImpl :: levelPrint() {
    AvlTreeHelper::levelPrint(this->root);
}