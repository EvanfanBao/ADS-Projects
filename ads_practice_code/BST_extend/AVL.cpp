// * An AVL tree is a self-balancing binary search 
// * tree. In an AVL tree, the heights of the two 
// * child subtrees of any node differ by at most one; 
// * if at any time they differ by more than one, 
// * rebalancing is done to restore this property. 
// *


#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

typedef struct AVLTree{
    int element;
    struct AVLTree *Left;
    struct AVLTree *Right;
    int height;
}AVLNode;

typedef AVLNode *pNode;
typedef pNode AVLT;
pNode Insert(int element, AVLT Tree);

//rotation operation!!
pNode RightSingleRotate(pNode node);
pNode LeftSingleRotate(pNode node);

pNode LRRotation(pNode node);
pNode RLRotation(pNode node);
int Height(pNode node);
int Max(int a, int b);

int main(){
    AVLT tree = NULL;
    int n,i;
    int *arr;
    cin >> n;
    arr = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n;i++){
        cin >> arr[i];
    }
    for(i = 0;i < n;i++){
        tree = Insert(arr[i],tree);
    }
    cout << tree->element;
}

pNode Insert(int element, AVLT Tree){

    if(Tree == NULL){
        Tree = (AVLT)malloc(sizeof(AVLNode));
        Tree->Left = NULL;
        Tree->Right = NULL;
        Tree->element = element;
        Tree->height = 0;
    }
    else{
        if(element < Tree->element){
            Tree->Left = Insert(element,Tree->Left);
            if(Height(Tree->Left)-Height(Tree->Right)==2){
                if(element < Tree->Left->element){
                    Tree = RightSingleRotate(Tree);
                }
                else Tree = LRRotation(Tree);
            }
        }
        else{
            Tree->Right = Insert(element,Tree->Right);
            if(Height(Tree->Right)- Height(Tree->Left) == 2){
                if(element > Tree->Right->element)
                    Tree = LeftSingleRotate(Tree);
                else Tree = RLRotation(Tree);
            }
        }
    }
    Tree->height = Max(Height(Tree->Left), Height(Tree->Right)) + 1;
    return Tree;
}

//node 是发生异常的点,右旋，从左向右旋转，记得高度更新,因该是保证存在了的
pNode RightSingleRotate(pNode node){
    pNode k1;
    k1 = node->Left;
    if(k1 != NULL){
    node->Left = k1->Right;
    k1->Right = node;
    node->height = Max(Height(node->Left),Height(node->Right))+1;  
    k1->height = Max(Height(k1->Left),Height(k1->Right))+1;
    return k1;
    }
}
//从右往左旋转
pNode LeftSingleRotate(pNode node){
    pNode k1;
    k1 = node->Right;
    if(k1 != NULL){
    node->Right = k1->Left;
    k1->Left = node;
    node->height = Max(Height(node->Left),Height(node->Right))+1;
    k1->height = Max(Height(k1->Left),Height(k1->Right))+1;
    return k1;
    }
}

//应该都保证存在的
//LRRotation还有一种实现方式--就是直接修改 不过传的的确都是父亲指针
pNode LRRotation(pNode node){
    pNode k1;
    k1 = node->Left;
    node->Left = LeftSingleRotate(k1);
    node = RightSingleRotate(node);
    return node;
}
pNode RLRotation(pNode node){
    pNode k1;
    k1 = node->Right;
    node->Right = RightSingleRotate(k1);
    node = LeftSingleRotate(node);
    return node;
}

int Height(pNode node){
    if(node == NULL)return -1;
    else return node->height;
}
int Max(int a, int b){
    return a>b?a:b;
}

