#include "AvlTreeHelper.h"

AvlTreeHelper :: AvlTreeHelper() {
}

AvlTreeHelper :: ~AvlTreeHelper() {
}

// get the path stack from a given node to where the insertKey exists or can be added
std::stack<std::pair<TreeNode*, Direction> > AvlTreeHelper :: getPathStack(TreeNode* cur, int insertKey) {
    TreeNode* prev;
    std::stack<std::pair<TreeNode*, Direction> > pathStack;
    Direction direction = N;

    // insert to stack and keep moving along the left sub-tree till condition is satisfied
    while(cur || !pathStack.empty()) {
        do {
            pathStack.push({cur, direction});
            direction = L;

            prev = cur;
            cur = cur->getLeft();
        } while(cur && prev->getData()->data > insertKey);

        cur = pathStack.top().first;

        int key = cur->getData()->data;

        // return pathstack if key is already present
        if(key == insertKey || AvlTreeHelper::isLeafNode(cur)) {
            return pathStack;
        }
        else if(key < insertKey) {
            cur = cur->getRight();

            // this is where we fall off from the tree, can be inserted here
            if(!cur) {
                return pathStack;
            }

            direction = R;
        }
        else {
            return pathStack; // return because, the keys after this point are higher than the insert key
        }
    }

    return pathStack;
}

// check if node is leaf node
bool AvlTreeHelper :: isLeafNode(TreeNode* cur) {
    return !cur->getLeft() && !cur->getRight();
}

// perform ll rotation
void AvlTreeHelper :: llRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* c = pp->getRight();

    gp->setLeft(c);
    pp->setRight(gp);
}

// perform rr rotation
void AvlTreeHelper :: rrRotation(TreeNode* gp, TreeNode* pp, TreeNode* p) {
    TreeNode* b = pp->getLeft();

    gp->setRight(b);
    pp->setLeft(gp);
}

// handle rotation of tree
TreeNode* AvlTreeHelper :: rotateTree(RotationType rotationType, TreeNode* cur) {
    TreeNode* newCur; // the new node goes to the top and gp and pp become it's children incase of lr or rl rotation
    TreeNode* gp;
    TreeNode* pp;
    TreeNode* p;

    switch(rotationType) {
        case LL: 
            newCur = cur->getLeft();
            llRotation(cur, cur->getLeft(), cur->getLeft()->getLeft());

            break;

        case RR:
            newCur = cur->getRight();
            rrRotation(cur, cur->getRight(), cur->getRight()->getRight());

            break;

        case LR:
            newCur = cur->getLeft()->getRight();

            gp = cur;
            pp = cur->getLeft()->getRight();
            p = cur->getLeft();

            rrRotation(cur->getLeft(), cur->getLeft()->getRight(), cur->getLeft()->getRight()->getRight()); // we perform ll rr first
            llRotation(gp, pp, p); // then we perform ll 

            break;

        case RL:
            newCur = cur->getRight()->getLeft();

            gp = cur;
            pp = cur->getRight()->getLeft();
            p = cur->getRight();

            llRotation(cur->getRight(), cur->getRight()->getLeft(), cur->getRight()->getLeft()->getLeft()); // we perform ll first
            rrRotation(gp, pp, p); // and then rr

            break;
    }

    return newCur;
}

// update the left and right subtree heights, this is done incase it's children's heights have changed
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

// calculates the balance factor of the node
int AvlTreeHelper :: getBalanceFactor(TreeNode* temp) {
    return temp->getLeftHeight() - temp->getRightHeight();
}

// determines the rotation type
RotationType AvlTreeHelper :: getRotationType(int balanceFactor, TreeNode* cur) {
    // positive value indicates LL or LR
    if(balanceFactor > 0) {
        TreeNode* left = cur->getLeft();

        // greater left subtree height indicates LL
        if(left->getLeftHeight() >= left->getRightHeight()) {
            return LL;
        }

        return LR;
    }

    TreeNode* right = cur->getRight();

    // greater right subtree height indicates RR
    if(right->getRightHeight() >= right->getLeftHeight()) {
        return RR;
    }

    return RL;
}

// inorder traversal to print all keys in ascending order
void AvlTreeHelper :: dfs(TreeNode* cur) {
    if(!cur) {
        return;
    }

    dfs(cur->getLeft());
    std::cout<<cur->getData()->data<<std::endl;
    dfs(cur->getRight());
}

// level order traversal to print keys
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

// this is used to update patch stack with previous highest element, this is used while deleting a node
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

// this is used to update patch stack with next lowest element, this is used while deleting a node
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