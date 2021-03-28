#include<iostream>
#include<vector>
#include<math.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define INF 0x3f3f3f3f          //infinite number to define the bound of every level
#define PRECISION 9999          // the precision random value between(0,1)

class Node{                     //class storing node information
public:
    int searchKey;              // the search key
    vector<Node*> Next;         // Next[i] means the ith level likned list
    int nodeLevel;
    Node(){}                    //different kinds of construction function
    Node(int key):searchKey(key){}
    Node(int key,int random_level):searchKey(key),nodeLevel(random_level){Next.resize(nodeLevel+1);}
};
class skipList{                         //class storing skip list information
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
void skipList::PrintList(){             //print every node's level position
    Node* x =  Header->Next[0];
    while(x->searchKey != INF){         //transverse every node
        cout << x->searchKey << "is on level " <<x->nodeLevel<<endl;
        x = x->Next[0];
    }
}
Node* skipList::MakeNode(int key,int level){    //construct a new node to insert into skip list
    Node* node = new Node;
    node->searchKey = key;node->nodeLevel = level;node->Next.resize(level+1);
    return node;
}
skipList::skipList(int mlevel):maxLevel(mlevel),Level(0){
    Header = new Node;   NIL = new Node;
    Header->searchKey = -INF;            //define smallest bounding
    NIL->searchKey = INF;                //NIL value is biggest
    Header->Next.resize(maxLevel+1);
    Header->nodeLevel = mlevel;          //Header is of maximum level
    for(int i = 0; i <= maxLevel;i++)    //Initialze Header
        Header->Next[i] = NIL;
}
Node* skipList::Search(int key){         //search operation in skip list
    Node *x = Header;
    int i;
    for( i = Level; i >= 0;i--){        //transverse every level
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];             //visit the next node
        }
    }
    x = x->Next[0];             // final state at level 0
    if(x->searchKey == key)  return x;
    else return NULL;           //fail
}
int skipList::RandomLevel(double p){ // p=1/2 in usual case
    int level = 0;
    double prob=rand()%(PRECISION+1)/(double)(PRECISION+1); //generate random number
    while(level <maxLevel){
        prob = rand()%(PRECISION+1)/(double)(PRECISION+1); //use random number to determine the level number
        if(prob >= p)break;
        level = level+1;
    }
    return level;
}
void skipList::Insert(int key){   //insertion operation in skip list
    Node* update[maxLevel];
    Node* x = Header;
    int i;
    for(i = Level;i >= 0;i--){   //Search -- record last updated node in each level of list
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
                update[i] = Header;         //higher than original structure, set header
            }
            Level = v;
        }
        x = MakeNode(key,v);
        for(i = 0;i <= v;i++){              //update connection
            x->Next[i] = update[i]->Next[i];
            update[i]->Next[i] = x;
        }
    }
}
void skipList::Delete(int key){     //deletion in skip list
    Node* update[maxLevel];
    Node* x = Header;
    int i;
    for(i = Level;i >= 0;i--){      //Search -- record last updated node in each level of list
        while(x->Next[i]->searchKey < key){
            x = x->Next[i];           //visit next node
        }
        update[i] = x;                  //update information
    }
    x = x->Next[0];
    if(x->searchKey == key){                        //Find
        for(i = 0; i <= Level;i++){
            if(update[i]->Next[i] != x)break;       //no key -- do nothing
            update[i]->Next[i] = x->Next[i];        //update connection
        }
        delete x;
    }
    while(Level > 0 && Header->Next[Level] == NIL){ //adjust the height of skip list
        Level--;                                    //remove blank ones
    }
}
int main(){                                 //to measure time more accurately
    int N,times;                                //define the number of operations and times of the program execution
    cout<<"Please enter the size of skip list: "<<endl;
    cin>>N;
    cout<<"Please enter the times the operation needs to be executed: "<<endl;
    cin>>times;
    srand( (unsigned)time( NULL ));
    double dur=0;
    clock_t start,end;
    skipList list;
    for(int i = 0;i < N;i++)  list.Insert(i);       //construct skip list of size N
    start = clock();  //start timing
    for(int j=0;j<times;j++)                        //do test many times
    {
        list.Search(rand()%N);                      //search random element
        int key=rand()%N;
        list.Insert(key);                           //insert and delete to ensure the size unchanged
        list.Delete(key);
    }
    end=clock();
    dur = (double)(end - start);
    cout<<"Hint: Use a larger times number for small size skip list or the result is not accurate."<<endl;
    cout<<endl<<"Running time of single operation on skiplist with size "<<N<<" is "<<(dur/CLOCKS_PER_SEC/times/3)<<endl; //print out time of single operation
    system("pause"); 
}
