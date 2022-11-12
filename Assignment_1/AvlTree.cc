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

        updateHeights(cur);

        int balanceFactor = this->getBalanceFactor(cur);
        if(balanceFactor == 0) {
            break;
        }
        else if(balanceFactor == 2 || balanceFactor == -2) {
            std::cout<<"Balancing has to be done. The balance factor is "<<balanceFactor<<std::endl;
            RotationType rotationType = this->getRotationType(balanceFactor, cur);
            cur = this->rotateTree(rotationType, cur);
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

void AvlTree :: updateHeights(TreeNode* temp) {
    if(temp->getLeft()) {
        temp->setLeftHeight(temp->getLeft()->getHeight() + 1);
    }
    else {
        temp->setLeftHeight(0);
    }
    if(temp->getRight()) {
        temp->setRightHeight(temp->getRight()->getHeight() + 1);
    }
    else {
        temp->setRightHeight(0);
    }
}

int AvlTree :: getBalanceFactor(TreeNode* temp) {
    return temp->getLeftHeight() - temp->getRightHeight();
}

RotationType AvlTree :: getRotationType(int balanceFactor, TreeNode* cur) {
    if(balanceFactor > 0) {
        TreeNode* left = cur->getLeft();

        if(left->getLeftHeight() > left->getRightHeight()) {
            std::cout<<"LL rotation to be done"<<std::endl;
            return LL;
        }

        std::cout<<"LR rotation to be done"<<std::endl;
        return LR;
    }

    TreeNode* right = cur->getRight();

    if(right->getRightHeight() > right->getLeftHeight()) {
        std::cout<<"RR rotation to be done"<<std::endl;
        return RR;
    }

    std::cout<<"RL rotation to be done"<<std::endl;
    return RL;
}

TreeNode* AvlTree :: rotateTree(RotationType rotationType, TreeNode* cur) {
    TreeNode* newCur;

    switch(rotationType) {
        case LL: 
            newCur = cur->getLeft();
            std::cout<<"Performing LL rotation"<<std::endl;
            llRotation(cur, cur->getLeft(), cur->getLeft()->getLeft());

            break;

        case RR:
            newCur = cur->getRight();
            std::cout<<"Performing RR rotation"<<std::endl;
            rrRotation(cur, cur->getRight(), cur->getRight()->getRight());

            break;

        case LR:
            newCur = cur->getLeft()->getRight();
            std::cout<<"Performing LR rotation"<<std::endl;
            rrRotation(cur->getLeft(), cur->getLeft()->getRight(), cur->getLeft()->getRight()->getRight());
            llRotation(cur, cur->getLeft(), cur->getLeft());

            break;

        case RL:
            newCur = cur->getRight()->getLeft();
            std::cout<<"Performing RL rotation"<<std::endl;
            llRotation(cur->getRight(), cur->getRight()->getLeft(), cur->getRight()->getLeft()->getLeft());
            rrRotation(cur, cur->getRight(), cur->getRight());

            break;
    }

    return newCur;
}

void AvlTree :: llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* c = pp->getRight();

    gp->setLeft(c);
    pp->setRight(gp);
    std::cout<<"LL rotation done"<<std::endl;
}

void AvlTree :: rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* b = pp->getLeft();

    gp->setRight(b);
    pp->setLeft(gp);
    std::cout<<"RR rotation done"<<std::endl;
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

void AvlTree :: levelPrint() {
    std::queue<TreeNode*> q;
    int level = 0;

    q.push(this->root);

    while(!q.empty()) {
        int size = q.size();

        std::cout<<"Level "<<level<<std::endl;

        for(int i=0;i<size;i++) {
            TreeNode* temp = q.front();
            q.pop();

            std::cout<<"The key is "<<temp->getData()->data<<std::endl;
            std::cout<<"It's children are "<<std::endl;
            if(temp->getLeft()) {
                std::cout<<"Left child "<<temp->getLeft()->getData()->data<<std::endl;

                q.push(temp->getLeft());
            }

            if(temp->getRight()) {
                std::cout<<"Right child "<<temp->getRight()->getData()->data<<std::endl;

                q.push(temp->getRight());
            }

            std::cout<<"Left height is "<<temp->getLeftHeight()<<" and Right height is "<<temp->getRightHeight()<<" and height is "<<temp->getHeight()<<std::endl;
            ++level;
        }
    }
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