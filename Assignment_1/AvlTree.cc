#include "AvlTree.h"

AvlTree :: AvlTree()  {
    this->root = nullptr;
}

AvlTree :: ~AvlTree()  {
    delete root;
}

const Key* AvlTree :: search(int key) {
    std::stack<TreeNode*> s;
    TreeNode* cur = this->root;
    TreeNode* prev;

    s.push(cur);

    while(cur || !s.empty()) {
        do {
            s.push(cur);

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data >= key);

        cur = s.top();
        s.pop();

        if(cur->getData()->data == key) {
            return cur->getData();
        }
        else if(cur->getData()->data < key) {
            cur = cur->getRight();
        }
    }

    return nullptr;
}

const std::vector<const Key*> AvlTree :: search(int low, int high) {
    std::vector<const Key*> keys;
    std::stack<TreeNode*> s;
    TreeNode* cur = this->root;
    TreeNode* prev;

    s.push(cur);

    while(cur || !s.empty()) {
        do {
            s.push(cur);

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data >= low);

        cur = s.top();
        s.pop();

        int key = cur->getData()->data;

        if(key >= low && key <= high) {
            keys.push_back(cur->getData());
        }

        if(key <= high) {
            cur = cur->getRight();
        }
    }

    return keys;
}

void AvlTree :: insert(int key) {
    std::cout<<"Inserting "<<key<<" into the tree"<<std::endl;
    std::stack<std::pair<TreeNode*, Direction> > pathStack = this->getPathStack(key);

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
        pathStack.top().first->setLeft(temp);
    }
    else {
        pathStack.top().first->setRight(temp);
    }
    pathStack.pop();

    while(!pathStack.empty()) {
        TreeNode* cur = pathStack.top().first;
        Direction direction = pathStack.top().second;
        pathStack.pop();

        updateHeights(cur);
        int balanceFactor = this->getBalanceFactor(cur);

        if(balanceFactor == 0) {
            break;
        }
        else if(balanceFactor == 2 || balanceFactor == -2) {
            RotationType rotationType = this->getRotationType(balanceFactor, cur);
            this->rotateTree(rotationType, cur);

            this->updateParent(cur, pathStack, direction);
            
            break;
        }
    }

    std::cout<<"Inserted "<<key<<" to the tree"<<std::endl;
}

void AvlTree :: updateHeights(TreeNode* temp) {
    temp->setLeftHeight(temp->getLeft()->getHeight());
    temp->setRightHeight(temp->getRight()->getHeight());
}

int AvlTree :: getBalanceFactor(TreeNode* temp) {
    return temp->getLeftHeight() - temp->getRightHeight();
}

RotationType AvlTree :: getRotationType(int balanceFactor, TreeNode* cur) {
    if(balanceFactor > 0) {
        TreeNode* left = cur->getLeft();

        if(left->getLeftHeight() > left->getRightHeight()) {
            return LL;
        }

        return LR;
    }

    TreeNode* right = cur->getRight();

    if(right->getRightHeight() > right->getLeftHeight()) {
        return RR;
    }

    return RL;
}

void AvlTree :: rotateTree(RotationType rotationType, TreeNode* cur) {
    switch(rotationType) {
        case LL: 
            llRotation(cur, cur->getLeft(), cur->getLeft()->getLeft());
            break;

        case RR:
            rrRotation(cur, cur->getRight(), cur->getRight()->getRight());
            break;

        case LR:
            rrRotation(cur->getLeft(), cur->getLeft()->getRight(), cur->getLeft()->getRight()->getRight());
            llRotation(cur, cur->getLeft(), cur->getLeft());
            break;

        case RL:
            llRotation(cur->getRight(), cur->getRight()->getLeft(), cur->getRight()->getLeft()->getLeft());
            rrRotation(cur, cur->getRight(), cur->getRight());
            break;
    }
}

void AvlTree :: llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* c = pp->getRight();

    gp->setLeft(c);
    pp->setRight(gp);
}

void AvlTree :: rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* b = pp->getLeft();

    gp->setRight(b);
    p->setLeft(gp);
}

void AvlTree :: updateParent(TreeNode* cur, std::stack<std::pair<TreeNode*, Direction> >& pathStack, Direction direction) {
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

void AvlTree :: print() {
    dfs(root);
}

void AvlTree :: dfs(TreeNode* cur) {
    if(!cur) {
        return;
    }

    dfs(cur->getLeft());
    std::cout<<cur->getData()->data<<std::endl;
    dfs(cur->getRight());
}

std::stack<std::pair<TreeNode*, Direction> > AvlTree :: getPathStack(int insertKey) {
    TreeNode* cur = this->root;
    TreeNode* prev;
    std::stack<std::pair<TreeNode*, Direction> > pathStack;
    Direction direction = N;

    while(cur || !pathStack.empty()) {
        do {
            pathStack.push({cur, direction});
            direction = L;

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data >= insertKey);

        cur = pathStack.top().first;

        int key = cur->getData()->data;

        if(key == insertKey || this->isLeafNode(cur)) {
            return pathStack;
        }
        else if(key < insertKey) {
            cur = cur->getRight();
            direction = R;
        }
    }

    std::cout<<"The path stack is empty"<<std::endl;

    return pathStack;
}

bool AvlTree :: isLeafNode(TreeNode* cur) {
    return !cur->getLeft() && !cur->getRight();
}