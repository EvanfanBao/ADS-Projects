#include<stdio.h>
#include<iostream>
#include<stdlib.h>
//https://www.geeksforgeeks.org/splay-tree-set-1-insert/
using namespace std;

typedef struct node Tnode;
struct node{
    int Key;
    Tnode *Left;
    Tnode *Right;
};
typedef Tnode *pnode;
typedef pnode splayT;

pnode Splay(splayT root,int key);
pnode LeftRotate(splayT node);
pnode RightRotate(splayT node);
pnode NewNode(int key);

int main(){
    splayT root = NewNode(11);
    root->Left = NewNode(5);
    //root->Left->Left = NewNode(4);
    //root->Left->Right = NewNode(6);
    //root->Right = NewNode(15);
    //root->Right->Right = NewNode(25);
    root = Splay(root,6);
    cout << root->Key;
}

pnode NewNode(int key){
    pnode node = (pnode)malloc(sizeof(Tnode));
    node->Key = key;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

//node 的右孩子，向左旋转--保证存在的情况
pnode LeftRotate(splayT node){
    pnode child = node->Right;
    node->Right = child->Left;
    child->Left = node;
    return child;
}
pnode RightRotate(splayT node){
    pnode child = node->Left;
    node->Left = child->Right;
    child->Right = node;
    return child;
}

//root is (sub)tree's root, key is the one you want to find(may nonexist, do nothing)
pnode Splay(splayT root,int key){
    //base case
    if(root == NULL || root->Key == key)
        return root;//do nothing
    if(key < root->Key){
        //key is not in tree, done
        if(root->Left == NULL)return root;

        if(key < root->Left->Key){
            root->Left->Left = Splay(root->Left->Left, key);
            root = RightRotate(root);
        }
        else if(key > root->Left->Key){
            root->Left->Right = Splay(root->Left->Right, key);
            if(root->Left->Right != NULL)
                root->Left = LeftRotate(root->Left);
        }
        //前面的NULL判断就是, 要查找的就是孩子到了原来根的左孩子的左孩子是空。但还是进行了一次根的rotate，所以不用再次rotate了
        //这也是没找到的情况。修改也可以是和它的另一个else语句一样，加一个条件判断。那么结果应该是一样的。
        return (root->Left == NULL) ? root:RightRotate(root);
    }
    else {
        if(root->Right == NULL)return root;
        if(key > root->Right->Key){
            root->Right->Right = Splay(root->Right->Right, key);
            root = LeftRotate(root);
        }
        else if(key < root->Right->Key){
            root->Right->Left = Splay(root->Right->Left,key);
            if(root->Right->Left != NULL)
                root->Right = RightRotate(root->Right);
        }
        return (root->Right == NULL) ? root: LeftRotate(root);
    }
}
