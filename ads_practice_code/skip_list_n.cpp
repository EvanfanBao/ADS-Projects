#include<iostream>
#include<vector>
#include<math.h>
#include <stdlib.h> 
#include <time.h>
using namespace std;


#define INF 100000              // Infinity, big enought number
#define PRECISION 9999          // The precision--random value between(0,1)

class Node{
public:

    // Constructor
    Node(){}
    Node(int key):searchKey(key){}
    Node(int key,int random_level):searchKey(key),nodeLevel(random_level){Next.resize(nodeLevel+1);}

    // Destructor
    ~Node();

    vector<Node*> Next;         // Next[i] means the ith level likned list, start from 0
    int searchKey;              // The search key
    int nodeLevel;              // Level of a nodes
};


class skipList{
public:

    // Contructor -- default maxLevel is 16 -- containing up to 2^16 elements
    skipList(int mlevel = 16);          
    // Destructor
    ~skipList();

    int maxLevel;                       // Maximum level of skipList
    int Level;                          // Current level of list
    Node* Header;                       // Dummy header
    Node* NIL;                          // Sentinal
    void Insert(int value);             // Insert a node with Key(value) to skip_list
    void Delete(int value);             // Delete a node with Key(value) from skip_list
    Node* Search(int value);            // Search a node with Key(value) from skip_list
    int RandomLevel(double p = 0.5);    // Generate node level according to probability -- default is 0.5
    
    void PrintList();                   // Debug
    Node* MakeNode(int key,int level);  // Make a node with specified key and level
    
};

// Clear the list
skipList::~skipList(){
    Node* p = Header;
    Node* pNext;
    while(p != NIL){
        pNext = p->Next[0];
        delete p;
        p = pNext;
    }
    delete NIL;

}

// Clear container
Node::~Node(){
    Next.clear();
}

// Debug Print
void skipList::PrintList(){
    Node* x =  Header->Next[0];
    while(x->searchKey != INF){
        cout << "searchkey " << x->searchKey << " level is " <<x->nodeLevel<<" " << endl;
        x = x->Next[0];
    }
}

// Make a node with specified key and level
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


// Default p=1/2 applicable only when MaxHeight is knows
int skipList::RandomLevel(double p){
    int level = 0;
    
    double prob;
    prob = rand()%(PRECISION+1)/(double)(PRECISION+1);      // Probability between (0,1)
    while(level < maxLevel){
        prob = rand()%(PRECISION+1)/(double)(PRECISION+1);
        if(prob >= p)break;
        level = level+1;
    }
    return level;
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
    if(x->searchKey == key) return;         // Already exist do nothing 
    else{
        int v = RandomLevel();
        if(v > Level){
            for(i = Level+1; i <= v;i++){
                update[i] = Header;         // Higher than the orignal list, hence last update is Header
            }
            Level = v;              
        }
        x = MakeNode(key,v);                // Make a new node
        for(i = 0;i <= v;i++){              // Update linking
            x->Next[i] = update[i]->Next[i];
            update[i]->Next[i] = x;
        }
    }
}


void skipList::Delete(int key){
    Node* update[maxLevel];
    Node* x = Header;
    int i;
    // Search -- record last updated node in each level of list
    for(i = Level;i >= 0;i--){
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];
        }
        update[i] = x;
    }
    x = x->Next[0];
    if(x->searchKey == key){                        //Find
        for(i = 0; i <= Level;i++){
            if(update[i]->Next[i] != x)break; 
            update[i]->Next[i] = x->Next[i];        // Update linking
        }   
        delete x;
    }
    // Adjust the list height
    while(Level > 0 && Header->Next[Level] == NIL){
        Level--;
    }
}

int main(){
    skipList list; 
    srand( (unsigned)time( NULL ));
    for(int i = 0;i < 1000;i++){
        list.Insert(i);
    }
    list.PrintList();
}