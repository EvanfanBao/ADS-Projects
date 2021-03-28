//堆里面元素是二叉树的根结点--root--指针，堆的key就是频率
//代码实现应该没问题，就是new 和 delete做的不好 对代码理解也不好
//需要改进

#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct node{
    int key;
    node* left;
    node* right;
    node(int x):key(x),left(NULL),right(NULL){}      // 构造函数
    node():left(NULL),right(NULL){}
    ~node(){}
};

struct bst{
    node* root;
    bool operator<(const bst& bt) const{
        return root->key < bt.root->key;
    }
    bool operator>(const bst& bt)const {
        return root->key > bt.root->key;
    }
    bst(){}
    bst(node* rt):root(rt){}
    ~bst(){}
};



bst Huffman(priority_queue < bst,vector<bst>,greater<bst> >& pq, int N)
{
    //bst tmp;
    node* tmp;
    int weight(0);
    bst bt;
    for( int i = 1;i <= N;i++){
        weight = 0;
        //bst bt;
        bt.root = new node;
        tmp = pq.top().root;pq.pop();weight += tmp->key;
        bt.root->left = tmp;
        tmp = pq.top().root;pq.pop();weight += tmp->key;
        bt.root->right = tmp;
        bt.root->key = weight;
        pq.push(bt);
        //bt.~bst();
    }
    return pq.top();
}


int main(){
    priority_queue < bst,vector<bst>,greater<bst> > pq;
    //priority_queue <int> pq;
    bst b;
    for(int i = 0;i < 7;i++){
        b.root = new node;
        cin >> b.root->key;
        pq.push(b);
    }
    // for(int i = 0; i < 7;i++){
    //     cout << pq.top().root->key << " ";pq.pop();
    // }
    b = Huffman(pq,7);
    cout << b.root->key;
    cout << b.root->left->key;
    cout << "no wrong";
}