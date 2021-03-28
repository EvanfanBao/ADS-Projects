#include<iostream>
#include<vector>
#include<map>
using namespace std;

typedef pair<string,float> wp;
const int N = 8; //七个
const int Infinity = 1000;

class BST{
    struct node{
        string key;
        node* left;
        node* right;
    };
    node* root;
    node* makeEmpty(node* t){
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }
    node* insert(string x,node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->key = x;
            t->left = t->right = NULL;
        }
        else if(x < t->key)
            t->left = insert(x,t->left);
        else if(x > t->key)
            t->right = insert(x,t->right);
        return t;
    }
    void inorder(node* t){
        if(t==NULL)
            return;
        inorder(t->left);
        cout << t->key <<" ";
        inorder(t->right);
    }
public:
    BST(){
        root = NULL;
    }
    ~BST(){
        root = makeEmpty(root);
    }
    void insert(string x){
        root = insert(x,root);
    }
    void display(){
        inorder(root);
        cout << endl;
    }
};




void OBST(wp word[],int n){
    //用数字记录根 n is the number of the sequence
    float w[n+2][n+2] = {0};// 权重 稍微设置大一点是为了后面的超出容限的时候值可以是0
    float cost[n+2][n+2] = {0}; //cost
    float nowcost;
    int root[n+2][n+2];
    for(int i = 1;i <= n;i++)
    {    
        cost[i][i] = word[i].second;     //cii = 0 
    }
    for(int i = 1;i <= n;i++)   
        for(int j = i;j <= n;j++)  
            for(int k = i;k <= j;k++){
                w[i][j] += word[k].second;
            }
    int i,j,k,L;//n = 7
    for(k=1;k<n;k++) //k = j-i
        for(i = 1;i+k <= n;i++){
            j = i+k;cost[i][j] = Infinity;
            for(L = i;L <= j;L++){
                nowcost = w[i][j]+cost[i][L-1]+cost[L+1][j];
                if(nowcost < cost[i][j])cost[i][j] = nowcost;
            }
        }
}





int main(){
    
    wp word[N];
    word[1] = make_pair("break",0.22);
    word[2] = make_pair("case",0.18);
    word[3] = make_pair("char",0.20);
    word[4] = make_pair("do",0.05);
    word[5] = make_pair("return",0.25);
    word[6] = make_pair("switch",0.02);
    word[7] = make_pair("void",0.08);
    BST bt;
    OBST(word,7);
    //bt.display();
}