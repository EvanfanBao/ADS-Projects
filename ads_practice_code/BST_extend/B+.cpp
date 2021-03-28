#include<iostream>
#include<string>

#define ORDER 3

typedef struct BPTreeNode BPNode;
struct BPTreeNode{
    bool Isleaf;
    int *key;
    BPNode* parent;
    BPNode** child;
    int key_num;

};
typedef BPNode* BPTree;

//empty tree
BPTree InitTree(){
    BPTree Root;
    int i;
    Root = (BPTree)malloc(sizeof(BPNode));
    Root->Isleaf = true;
    Root->key = new int[ORDER]; //现在是叶子，应该可以存4个的
    Root->child = new BPNode*[1];// 指向右边
    Root->child[0] = NULL;
    Root->key_num = ORDER;
    return Root;
}

bool Search(int x,BPTree root){
    BPNode* node = root;
    int i = 0;
    while(!node->Isleaf){//线性比较
        while(x >= node->key[i]){
            i++;
        }
        node = node->child[i];
    }
    //node是leaf 了
    for(i = 0;i < node->key_num;i++){
        if(x == node->key[i])
            return 1;
    }
    return 0;
}


BPTree Insert(int x, BPTree root){
    BPTreeNode *node = root;
    BPTreeNode *parent = node;
    int i = 0;
    //是leaf
    for(i = 0;i < node->key_num;i++){
        if(x <= node->key[i])break;
    }
    if(x == node->key[i])
        cout << "Key" << x << "is duplicated" << endl;
    else{
        node->key_num++;
        if(node->key_num > ORDER){
            split()
        }
    }   
}


using namespace std;

int main(){
    int n;
    cin >> n;

}