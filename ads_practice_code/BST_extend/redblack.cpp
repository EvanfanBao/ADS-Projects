//红黑树的5条性质
//1. either red or black
//2. root is black
//3. NIL is black  有时候真的不懂这个哨兵怎么实现
//4. a node is red, both its children are black
//5. for each node, all simple paths from the node to descendant leaves contain the same number of black nodes
//非红即黑，根黑，哨兵黑，红夫黑子，黑高
//黑高--从x到它任意一个叶子的路径上黑结点的个数(有时候包括，有时候不包括)
//高度是O(logN)  h <= 2log(N+1)。首先归纳法证明任意结点
//2^bh(x)-1 >= sizeof(x)---就是x为子根的子树元素个数
//再证明黑高大于等于树高的一半---红黑树的性质


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

struct node{
    int key;
    int color;      //0 for red, 1 for black
    struct node *left;
    struct node *right;
    struct node *parent;
};


typedef struct node* pnode;

struct RBT{
    pnode root;
    pnode NIL;
};
typedef struct RBT RBT;

using namespace std;
RBT RB_Insert(RBT T, int key);
RBT RB_Insert_Fixup(RBT T, pnode z);
RBT LeftRotate(RBT T,pnode node);
RBT RightRotate(RBT T,pnode node);


int main(){
    //initialize
    struct RBT T;
    T.NIL = (pnode)malloc(sizeof(struct node));
    T.NIL->color = 1;
    T.NIL->key = 0;
    T.NIL->left = T.NIL->right = T.NIL->parent = T.NIL;
    T.root = T.NIL;
    T = RB_Insert(T,5);
    T = RB_Insert(T,10);
    //T = LeftRotate(T,T.root);
    T = RB_Insert(T,15);
    T = RB_Insert(T,18);
    cout << T.root->right->color;
}

// pnode NewNode(int key){
//     pnode node = (pnode)malloc(sizeof(struct node));
//     node->key = key;
//     node->color = 0;//red

// }

RBT RB_Insert(RBT T, int key){

    //new node
    pnode node = (pnode)malloc(sizeof(struct node));
    node->key = key;
    node->left = T.NIL;
    node->right = T.NIL;
    node->color = 0; //red
    //cout << node->key;
    //root--iteration---直到nil停止--空树的话root就等于nil的--
    pnode root = T.root;
    pnode p = T.NIL; //parent

    while(root != T.NIL){
        p = root;
        if(key > root->key)
            root = root->right;
        else root = root->left;
    }
    node->parent = p;
    //没有根结点，只有nil，空树
    if(p == T.NIL)
        T.root = node;
    else if(key < p->key)  
        p->left = node;
    else p->right = node;
    T = RB_Insert_Fixup(T, node);
    return T;
}
RBT RB_Insert_Fixup(RBT T, pnode z){
    //出问题
    while(z->parent->color == 0){
        if(z->parent == z->parent->parent->left){
            //父红叔叔红-》父黑叔叔黑，祖父红-变为可能出问题点
            if(z->parent->parent->right->color == 0){
                z->parent->color = z->parent->parent->right->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else if(z->parent->parent->right->color == 1){
                if(z == z->parent->right)   
                    T = LeftRotate(T,z->parent);        // case3
                z->parent->color = 1;                   // case4
                z->parent->parent->color = 0;
                T = RightRotate(T,z->parent->parent);
            }
        }
        else {
            if(z->parent->parent->left->color == 0){
                z->parent->color = z->parent->parent->left->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else if(z->parent->parent->left->color == 1){
                if(z == z->parent->left)   
                    T = RightRotate(T,z->parent);
                z->parent->color = 1;
                z->parent->parent->color = 0;
                T = LeftRotate(T,z->parent->parent);
            }
        }
    }
    T.root->color = 1;
    return T;
}

// 红黑树的rotate 稍微复杂一点 要判断NIL 要判断parent
RBT LeftRotate(RBT T,pnode node){
    pnode child = node->right;
    node->right = child->left;
    if(child->left != T.NIL)
        child->left->parent = node;  //我们希望nil的parent为根，因为就一个根
    child->parent = node->parent;
    if(node->parent == T.NIL)       //这里的判断还是比较复杂的，主要就是AVL树是递归实现，所以不用考虑父子关系
        T.root = child;              //这里的rotate就是单纯的操作，祖父和父亲的连接要变的
    else if(node = node->parent->left){
        node->parent->left = child;
    }
    else node->parent->right = child;
    child->left = node;
    node->parent = child;
    return T;
}

RBT RightRotate(RBT T,pnode node){
    pnode child = node->left;
    node->left = child->right;
    if(child->right != T.NIL)
        child->right->parent = node->left;
    child->parent = node->parent;
    if(node->parent == T.NIL)
        T.root = child;
    else if(node == node->parent->left)
        node->parent->left = child;
    else node->parent->right = child;
    child->right = node;
    node->parent = child;
    return T;
}

// DELETE操作有机会实现一下