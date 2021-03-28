#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
#define MAX 10


// binomial queue
typedef struct Node Node;
typedef Node* Tnode;
// first child next sibling
struct Node{
    int Key;
    Tnode FirstChild;
    Tnode NextSibling;
};

struct BinoQue{
    int CurrentSize;    // number of nodes
    Node *bq[MAX];
};
typedef struct BinoQue* BQ; 


BQ Initialize();
int FindMin(BQ Q1);
BQ Merge(BQ Q1,BQ Q2);
int DeleteMin(BQ Q1);
BQ Insert(BQ Q1, int key);
Tnode NewNode(int key);
Tnode CombineTrees(Tnode T1, Tnode T2);


//insert is a special case of merge  merge takes O(logN), but amortized time of insertion is O(1)
//find min is part of deletemin  --- O(logN)



BQ Initialize(){
    BQ binq = (BQ)malloc(sizeof(struct BinoQue));
    int i;
    binq->CurrentSize = 0;
    for(i = 0; i < MAX; i++)
        binq->bq[i] = NULL;     //空的都是NULL
    return binq;
}


// combine two binomial trees, T1 T2 are same size. Let T1 be the root
Tnode CombineTrees(Tnode T1, Tnode T2){
    if(T1->Key > T2->Key)
        return CombineTrees(T2, T1);
    T2->NextSibling = T1->FirstChild;
    T1->FirstChild = T2;
    return T1;
}


// 老师说千万别看，一定要自己想--自己实现--我还是没做到，sigh
// merge到Q1
BQ Merge(BQ Q1,BQ Q2){
    int i,j;
    Tnode Carry = NULL;
    Tnode T1, T2;
    Q1->CurrentSize += Q2->CurrentSize;  //Q1新的大小
    //这里是对应T1 T2 Carry  , 用j每次乘2，是因为根最大位logN，所以每次乘2，直到N,就遍历了所有的根了
    for(i = 0,j = 1; j <= Q1->CurrentSize; j *= 2, i++){
        T1 = Q1->bq[i], T2 = Q2->bq[i];
        //这里清空有什么用？Carry清空很重要，因为下一次用的时候，如果已经用过carry了，carry是没有了的。
        //T2清空有用吗？自己还是想的太少了
        switch(4 * !!T1 + 2 * !!T2 + !!Carry){
            case 0: break;
            case 1: Q1->bq[i] = Carry;Carry = NULL;break;
            case 2: Q1->bq[i] = T2;Q2->bq[i] = NULL;break;
            case 3: Carry = CombineTrees(T2,Carry);Q2->bq[i] = NULL;break;
            case 4: break;
            case 5: Carry = CombineTrees(T1,Carry);Q1->bq[i] = NULL;break;
            case 6: Carry = CombineTrees(T1,T2);Q1->bq[i] = NULL;Q2->bq[i] = NULL;break;
            case 7: Q1->bq[i] = Carry;Carry = CombineTrees(T1,T2),Q2->bq[i] = NULL;break;
        }
    }
    return Q1;
}


//1 找到 2 移除 3 删除 4 合并   
int DeleteMin(BQ Q1){
    int i,min_value;
    int min_idx = FindMin(Q1);//1 find
    Tnode MinNode = Q1->bq[min_idx];
    Tnode child;
    BQ NewQ = Initialize();
    min_value = MinNode->Key;
    child = MinNode->FirstChild;
    Q1->bq[min_idx] = NULL; //2 remove
    //下标是多少，就表示它是什么Bk，也就是它有的孩子的个数是确定的
    //第一个孩子是最大的
    NewQ->CurrentSize = (1<<min_idx) - 1;
    for(i = min_idx-1;i >= 0;i--){
        NewQ->bq[i] = child;
        child = child->NextSibling;
        NewQ->bq[i]->NextSibling = NULL;   //现在每个都是根了，所以右兄弟没了
    }
    free(MinNode);
    Q1 = Merge(Q1,NewQ);
    return min_value;
}

Tnode NewNode(int key){
    Tnode node = (Tnode)malloc(sizeof(Node));
    node->FirstChild = NULL;
    node->NextSibling = NULL;
    node->Key = key;
    return node;
}
BQ Insert(BQ Q1, int key){
    BQ NewBQ = Initialize();
    NewBQ->bq[0] = NewNode(key);
    NewBQ->CurrentSize = 1;
    Q1 = Merge(Q1,NewBQ);
    return Q1;
}

int FindMin(BQ Q1){
    int i,j;
    int min_idx;
    min_idx = 0;
    for(i = 0,j = 1;j <= Q1->CurrentSize; i++, j *= 2){
        if(Q1->bq[i]->Key < Q1->bq[min_idx]->Key)
            min_idx = i;
    }
    return min_idx;
}


int main(){
    BQ binq = Initialize();
    binq = Insert(binq,1);
    binq = Insert(binq,2);cout << binq->bq[1]->FirstChild->Key;
    binq = Insert(binq,3);cout << binq->bq[0]->Key;
    binq = Insert(binq,4);cout << binq->bq[2]->FirstChild->FirstChild->Key;
    // Insert(binq,5);
    // Insert(binq,6);
    // Insert(binq,7);
}