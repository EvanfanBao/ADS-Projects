#include<iostream>
#include<vector>
#include<math.h>
#include <stdlib.h> 
#include <time.h>
using namespace std;


#define INF 1000
#define PRECISION 9999          // the precision random value between(0,1)

class Node{
public:
    int searchKey;              // the search key
    vector<Node*> Next;         // Next[i] means the ith level likned list  --- 注意下标越界之类的问题---插入的时候要注意大小
    int nodeLevel;
    Node(){}
    Node(int key):searchKey(key){}
    Node(int key,int random_level):searchKey(key),nodeLevel(random_level){Next.resize(nodeLevel+1);}
};

class skipList{
public:
    int maxLevel;
    int Level;                          //current level of list
    Node* Header;
    Node* NIL;
    void Insert(int value);             //Insert a node with Key(value) to skip_list
    void Delete(int value);             //Delete a node with Key(value) from skip_list
    Node* Search(int value);            //Search a node with Key(value) from skip_list
    int RandomLevel(double p = 0.5);    //Generate node level according to probability -- default is 0.5
    skipList(int mlevel = 16);          //Contructor -- default maxLevel is 16 -- containing up to 2^16 elements
    void PrintList();                   //debug
    Node* MakeNode(int key,int level);  //make a node with specified key and level
};



void skipList::PrintList(){
    Node* x =  Header->Next[0];
    while(x->searchKey != INF){
        cout << "searchkey "<< x->searchKey << " level is " <<x->nodeLevel<<" " <<endl;
        x = x->Next[0];
    }
}

Node* skipList::MakeNode(int key,int level){
    Node* node = new Node;
    node->searchKey = key;node->nodeLevel = level;node->Next.resize(level+1);
    return node;
}

skipList::skipList(int mlevel):maxLevel(mlevel),Level(0){
    Header = new Node;         
    NIL = new Node; 
    Header->searchKey = -INF;
    NIL->searchKey = INF;                //NIL value is biggest
    Header->Next.resize(maxLevel+1);
    Header->nodeLevel = mlevel;          //Header is of maximum level
    for(int i = 0; i <= maxLevel;i++)    //Initialze Header
        Header->Next[i] = NIL;
}

Node* skipList::Search(int key){
    Node *x = Header;
    int i;
    for( i = Level; i >= 0;i--){
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];
        }
    }
    x = x->Next[0];             // 最终到第0层
    if(x->searchKey == key)  
        return x;
    else return NULL;           //fail
}

// 默认取p=1/2
// 此方法在MaxHeight已知的情况下使用
int skipList::RandomLevel(double p){
    int level = 0;
    
    double prob;
    prob = rand()%(PRECISION+1)/(double)(PRECISION+1); //第一次产生总是0.6几？
    while(level <maxLevel){
        prob = rand()%(PRECISION+1)/(double)(PRECISION+1);
        if(prob >= p)break;
        level = level+1;
    }
    
}


void skipList::Insert(int key){
    Node* update[maxLevel];
    Node* x = Header;
    int i;
    //Search -- record last updated node in each level of list
    for(i = Level;i >= 0;i--){
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];
        }
        update[i] = x;
    }
    x = x->Next[0];                         
    if(x->searchKey == key) return;         //do nothing -- 
    else{
        int v = RandomLevel();
        if(v > Level){
            for(i = Level+1; i <= v;i++){
                update[i] = Header;         //比原来链表还高---因此多出来的那部分的前驱是Header
            }
            Level = v;              
        }
        x = MakeNode(key,v);
        for(i = 0;i <= v;i++){              //每一次更新连接关系
            x->Next[i] = update[i]->Next[i];
            update[i]->Next[i] = x;
        }
    }
}


void skipList::Delete(int key){
    Node* update[maxLevel];
    Node* x = Header;
    int i;
    //Search -- record last updated node in each level of list
    for(i = Level;i >= 0;i--){
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];
        }
        update[i] = x;
    }
    x = x->Next[0];
    if(x->searchKey == key){                        //Find
        for(i = 0; i <= Level;i++){
            if(update[i]->Next[i] != x)break;       //不存在key--或者是 没有指向x了就break -- do nothing
            update[i]->Next[i] = x->Next[i];        //更新所有连接关系
        }   
        delete x;
    }
    //链表高度调整---可能删除了表内最高的结点
    while(Level > 0 && Header->Next[Level] == NIL){
        Level--;
    }
}

int main(){
    skipList list; 
    // for(int i = 0;i < 10;i++){
    //     list.Insert(i);
    // }
    
        list.RandomLevel();
        //cout << list.RandomLevel();
    //list.PrintList();
    
}