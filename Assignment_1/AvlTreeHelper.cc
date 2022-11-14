#include "AvlTreeHelper.h"

AvlTreeHelper :: AvlTreeHelper() {
}

AvlTreeHelper :: ~AvlTreeHelper() {
}

std::stack<std::pair<TreeNode*, Direction> > AvlTreeHelper :: getPathStack(TreeNode* cur, int insertKey) {
    TreeNode* prev;
    std::stack<std::pair<TreeNode*, Direction> > pathStack;
    Direction direction = N;

    while(cur || !pathStack.empty()) {
        do {
            pathStack.push({cur, direction});
            direction = L;

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data > insertKey);

        cur = pathStack.top().first;

        int key = cur->getData()->data;

        if(key == insertKey || AvlTreeHelper::isLeafNode(cur)) {
            return pathStack;
        }
        else if(key < insertKey) {
            cur = cur->getRight();

            // if degree is one, insert here and return
            if(!cur) {
                return pathStack;
            }

            direction = R;
        }
        else {
            return pathStack;
        }
    }

    std::cout<<"The path stack is empty"<<std::endl;

    return pathStack;
}

bool AvlTreeHelper :: isLeafNode(TreeNode* cur) {
    return !cur->getLeft() && !cur->getRight();
}

void AvlTreeHelper :: llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* c = pp->getRight();

    gp->setLeft(c);
    pp->setRight(gp);
    std::cout<<"LL rotation done"<<std::endl;
}

void AvlTreeHelper :: rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* b = pp->getLeft();

    gp->setRight(b);
    pp->setLeft(gp);
    std::cout<<"RR rotation done"<<std::endl;
}

TreeNode* AvlTreeHelper :: rotateTree(RotationType rotationType, TreeNode* cur) {
    TreeNode* newCur;
    TreeNode* gp;
    TreeNode* pp;
    TreeNode* p;

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

            gp = cur;
            pp = cur->getLeft()->getRight();
            p = cur->getLeft();

            std::cout<<"Performing LR rotation"<<std::endl;
            rrRotation(cur->getLeft(), cur->getLeft()->getRight(), cur->getLeft()->getRight()->getRight());
            llRotation(gp, pp, p);

            break;

        case RL:
            newCur = cur->getRight()->getLeft();

            gp = cur;
            pp = cur->getRight()->getLeft();
            p = cur->getRight();

            std::cout<<"Performing RL rotation"<<std::endl;
            llRotation(cur->getRight(), cur->getRight()->getLeft(), cur->getRight()->getLeft()->getLeft());
            rrRotation(gp, pp, p);

            break;
    }

    return newCur;
}

void AvlTreeHelper :: updateHeights(TreeNode* temp) {
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

int AvlTreeHelper :: getBalanceFactor(TreeNode* temp) {
    return temp->getLeftHeight() - temp->getRightHeight();
}

RotationType AvlTreeHelper :: getRotationType(int balanceFactor, TreeNode* cur) {
    if(balanceFactor > 0) {
        TreeNode* left = cur->getLeft();

        if(left->getLeftHeight() >= left->getRightHeight()) {
            std::cout<<"LL rotation to be done"<<std::endl;
            return LL;
        }

        std::cout<<"LR rotation to be done"<<std::endl;
        return LR;
    }

    TreeNode* right = cur->getRight();

    if(right->getRightHeight() >= right->getLeftHeight()) {
        std::cout<<"RR rotation to be done"<<std::endl;
        return RR;
    }

    std::cout<<"RL rotation to be done"<<std::endl;
    return RL;
}

void AvlTreeHelper :: dfs(TreeNode* cur) {
    if(!cur) {
        return;
    }

    dfs(cur->getLeft());
    std::cout<<cur->getData()->data<<std::endl;
    dfs(cur->getRight());
}

void AvlTreeHelper :: levelPrint(TreeNode* cur) {
    std::queue<TreeNode*> q;
    int level = 0;

    q.push(cur);

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
        }

        ++level;
    }
}

void AvlTreeHelper :: getPrevHighest(std::stack<std::pair<TreeNode*, Direction> >& pathStack) {
    TreeNode* cur = pathStack.top().first;
    if(!cur->getLeft()) {
        return;
    }

    cur = cur->getLeft();
    pathStack.push({cur, L});
    cur = cur->getRight();

    while(cur) {
        pathStack.push({cur, R});
        cur = cur->getRight();
    }
}

void AvlTreeHelper :: getNextLowest(std::stack<std::pair<TreeNode*, Direction> >& pathStack) {
    TreeNode* cur = pathStack.top().first;
    if(!cur->getRight()) {
        return;
    }

    cur = cur->getRight();
    pathStack.push({cur, R});
    cur = cur->getLeft();

    while(cur) {
        pathStack.push({cur, L});
        cur = cur->getLeft();
    }
}