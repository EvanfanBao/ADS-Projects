#include<iostream>
#include<stdlib.h>
#include<queue>


using namespace std;
#define ORDER 3 //就是2-3树，根2或3个孩子，叶子最多三个点，
                //也就是说叶子的key的个数最多为3，叶子除了
                //是根且刚插入的情况下，其他情况大于等于2
                //非叶子结点的key的个数最多为2，最少为1，
                //孩子个数为key的个数+1，最多为3，最少为2，
                //非叶子的key存的是第二个孩子开始每组的最小值

typedef struct BPTreeNode BPNode; //树的结点
struct BPTreeNode{
    bool Isleaf;                  //是否是叶子，叶子的key的个数为3，非叶子为2
    int key[100];                 //存储key数组,设置大一点方便移动
    BPNode* parent;               //父亲的指针
    BPNode* child[100];           //孩子的指针数组,设置大一点方便移动和调换
    int key_num;                  //key的个数，非叶子最多两个，叶子三个key
};

typedef BPNode* BPTree;            


//empty tree
BPTree InitTree(){
    BPTree Root;
    Root = (BPTree)malloc(sizeof(BPNode)); //分配
    Root->Isleaf = true;                   //根，空，叶子
    Root->parent = NULL;                   //无父亲
    Root->key_num = 0;                     //空，无值
    Root->child[0] = NULL;                 //就当是0+1，有一个孩子吧
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



/* */


///newNode 和 inittree差不多

int FindMin(BPNode* node){
    while(node != NULL && !node->Isleaf){
        node = node->child[0];
    }
    return node->key[0];
}

BPNode* Insert(int x, BPTree root){
    BPNode *node = root;   //tmp node
    BPNode *LeafNode;      //leafnode
    BPNode *parent;
    BPNode *NewRoot;
    BPNode *NewNode;
     
    int i = 0;
    int j;
    if(root->Isleaf && root->key_num == 0){
        root->key[0] = x;
        root->key_num++;
        return root;
    }
    
    //找到正确的插入的leaf位置
    while(!node->Isleaf){
        while(i < node->key_num && x >= node->key[i]){
            i++;
        }
        node = node->child[i];
    }

    //找到要插入的正确位置
    for(i = 0;i < node->key_num;i++){
        if(x <= node->key[i])break;
    }
    //有重复，return
    if(x == node->key[i])
    {   cout << "Key" <<" " << x << " is duplicated" << endl;
        return root; 
    }

    //移动 插入
    if(i == node->key_num){
        node->key[i] = x;
        node->key_num++;
    }
    else{
        for(j = node->key_num-1; j >= i; j--){
                node->key[j+1] = node->key[j]; 
            }
    //更新元素个数
        node->key[i] = x;
        node->key_num++;
       
    }
    
    //记录父亲，如果是根，没有父亲---其实也可以null
    if(node != root)parent = node->parent;

    //超过了个数，对叶子split，同时迭代检查parent，更新，root特殊处理
    //本来是可以一起迭代的，就是非叶结点和叶子结点个数差1，搞不来
    if(node->key_num > ORDER){
        LeafNode = InitTree();  //InitTree和新生成一个叶子结点差不多吧

        //从一半的位置开始移动，把一半的值移过去，这样新的leaf就有了
        for(i = (node->key_num)/2 ;i < node->key_num;i++){
            LeafNode->key[(LeafNode->key_num)++] = node->key[i];
        }
        
        //更新自己结点个数
        LeafNode->key_num = node->key_num - node->key_num/2;
        node->key_num = node->key_num/2;


        //如果本身是根，然后变成了两个，所以
        if(root == node){
            NewRoot = InitTree();                       //新根
            NewRoot->key_num = 1;                       //新根的key是1个，两个孩子
            NewRoot->Isleaf = false;                    //根，肯定不是leaf了
            NewRoot->child[0] = node;                   //一个是原来的结点
            NewRoot->child[1] = LeafNode;               //一个是新的
            NewRoot->key[0] = LeafNode->key[0]; //根的key要加一个，因为本身是叶子，所以直接给值就行，不然要找最小
            LeafNode->parent = NewRoot;
            root = NewRoot;
            return root;
            }
        //如果本身不是根，那就parent的指针多加一个，key的个数加1，新加的key的值就是分出去的第一个值
        else{
            parent->child[++(parent->key_num)] = LeafNode;
            parent->key[parent->key_num-1] = LeafNode->key[0];  //parent的key要加一个
            LeafNode->parent = parent;

            while(parent->key_num >= ORDER){
                NewNode = InitTree();
                NewNode->Isleaf = false;

                //移动一半的孩子
                for(i = (parent->key_num+1)/2 ;i < parent->key_num+1;i++){
                    NewNode->child[(NewNode->key_num)++] = parent->child[i];
                }
                //更新key的个数
                NewNode->key_num--;
                parent->key_num = parent->key_num - NewNode->key_num -1;
                NewNode->key[0] = FindMin(NewNode->child[1]); ///这里只对3阶有用，通用的再加个循环把所有key都搞出来
                //3阶每次split必定是2，2 均分，然后每个一个
                //如果本身就是根了，再加一个新根
                if(parent == root){
                    NewRoot = InitTree();                       
                    NewRoot->key_num = 1;
                    NewRoot->Isleaf = false;                    
                    NewRoot->child[0] = parent;
                    NewRoot->child[1] = NewNode;               
                    NewRoot->key[0] = FindMin(NewNode);
                    root = NewRoot;
                    return root;
                }
                else{
                    parent = parent->parent;
                    parent->child[++(parent->key_num)] = NewNode;
                    //更新key值
                    parent->key[parent->key_num-1] = FindMin(parent->child[parent->key_num]);
                    NewNode->parent = parent;
                }
            }
        }      
    }
    return root;
}





    

//using namespace std;

int main(){
    int n;
    BPTree Tree;
    BPTree tmp;
    Tree = InitTree();
    cin >> n;
    int i;
    int data;
    for(i = 0; i < n;i++){
        cin >> data;
        Tree = Insert(data,Tree);
    }
    //cout << Tree->child[0]->key_num;

    tmp = Tree;

    int flag = 0;

    queue<BPTreeNode*>q;
    if(tmp != NULL){
        q.push(tmp);
        q.push(NULL);
    }

    while(!q.empty()){
        tmp = q.front();
        q.pop();
        if(tmp == NULL){
            cout << "\n";
        }
        else{
        for(i = 0;i < tmp->key_num+1;i++){
            if(tmp->child[0] == NULL)break;
            q.push(tmp->child[i]);
        }
        if(tmp->child[0] != NULL)q.push(NULL); // NULL作为结束标志

        cout <<'[' ;
        flag = 0;
        for(i = 0;i < tmp->key_num;i++){
            if(flag == 0){
                cout << tmp->key[i];
                flag = 1;
            }
            else{
                cout << ','<< tmp->key[i];
            }
        }
        cout << ']';
        }
    }
}