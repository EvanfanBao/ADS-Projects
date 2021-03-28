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

void SortChild(BPTreeNode *parent);

typedef BPNode* BPTree;            

void Sort(BPTreeNode *parent);
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
    int chi; // 插入的位置是父亲的第几个孩子
    BPNode *tmpnode;
     
    int i = 0;
    int j;
    if(root->Isleaf && root->key_num == 0){
        root->key[0] = x;
        root->key_num++;
        return root;
    }
    
    //找到正确的插入的leaf位置
    while(node != NULL && !node->Isleaf){
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
            node->parent = NewRoot;   //也得设置parent，不然后面到时候分裂他的时候就是NULL了
            LeafNode->parent = NewRoot;
            root = NewRoot;
            return root;
        }
        //如果本身不是根，那就parent的指针多加一个，key的个数加1，新加的key的值就是分出去的第一个值
        else{
            for(i = 0;i < parent->key_num+1;i++){
                if(parent->child[i]==node){
                    chi = i;break;
                }
            }
            for(i = parent->key_num;i > chi;i--){
                parent->child[i+1] = parent->child[i];
            }
            parent->child[chi+1] = LeafNode;parent->key_num++;
            //parent->child[++(parent->key_num)] = LeafNode;  //！！！这里不能直接加在最后的，分裂后应该是加在分裂的那个key的位置的右边
            parent->key[parent->key_num-1] = LeafNode->key[0];  //parent的key要加一个
            LeafNode->parent = parent;
            //这里要注意，大小比较！！，key后面加进去的不一定就是大的
            Sort(parent);//sort key
            //sort(parent->key,&(parent->key[parent->key_num-1]));  //s!!!!
            //SortChild(parent);//算了，不写通用的了。

            while(parent->key_num >= ORDER){
                NewNode = InitTree();
                NewNode->Isleaf = false;

                //移动一半的孩子
                for(i = (parent->key_num+1)/2 ;i < parent->key_num+1;i++){
                    NewNode->child[(NewNode->key_num)++] = parent->child[i];
                }
                //更新key的个数，大不了都是1修改
                NewNode->key_num = 1;//NewNode->key_num--;
                parent->key_num=1;//parent->key_num = parent->key_num - NewNode->key_num -1;
                parent->key[0] = FindMin(parent->child[1]);///新加的，应该需要！！！
                NewNode->key[0] = FindMin(NewNode->child[1]); ///这里只对3阶有用，通用的再加个循环把所有key都搞出来
                //3阶每次split必定是2，2 均分，然后每个一个
                //NewNode->parent = parent->parent;   //应该没问题，可能有问题，也可以放后面
                //如果本身就是根了，再加一个新根
                if(parent == root){
                    NewRoot = InitTree();                       
                    NewRoot->key_num = 1;
                    NewRoot->Isleaf = false;                    
                    NewRoot->child[0] = parent;
                    NewRoot->child[1] = NewNode;               
                    NewRoot->key[0] = FindMin(NewNode);
                    parent->parent = NewRoot;      //应该是需要的
                    NewNode->parent = NewRoot;     //应该是需要的
                    root = NewRoot;
                    return root;
                }
                else{
                    tmpnode = parent;  //原来的parent，发生了split
                    parent = parent->parent; //原来parent的parent
                    for(i = 0;i < parent->key_num+1;i++){
                        if(parent->child[i]==tmpnode){
                        chi = i;break;
                        }
                    }
                    for(i = parent->key_num;i > chi;i--){
                        parent->child[i+1] = parent->child[i];
                    }
                    parent->child[chi] = NewNode;parent->key_num++;
                    //parent->child[++(parent->key_num)] = NewNode;
                    //更新key值
                    parent->key[parent->key_num-1] = FindMin(NewNode);
                    NewNode->parent = parent;
                    Sort(parent);
                    //SortChild(parent);
                    
                }
            }
        }      
    }
    return root;
}
void SortChild(BPTreeNode *parent){
    BPTreeNode *Tmpchild[100];
    int i,j;
    for(i = 0; i < parent->key_num+1;i++){
        Tmpchild[i] = parent->child[i];
    }
    for(i = 0;i < parent->key_num;i++){
        for(j = 0; j < parent->key_num+1;j++){
            if(FindMin(Tmpchild[j]) == parent->key[i]){
                parent->child[i+1] = Tmpchild[j];
            }
        }
    }
    //第0个应该不用变
}


void Sort(BPTreeNode *parent){
    int i,j;
    int t;
    int flag = 0;
    
    

    //对key进行排序
    for(i = 0; i < parent->key_num;i++){
        for(j = i; j < parent->key_num-1;j++){
            if(parent->key[j+1] < parent->key[j]){
                t = parent->key[j+1];
                parent->key[j+1] = parent->key[j];
                parent->key[j] = t;
            }
        } 
    }
    
    
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
    int childnum = 0;
    BPTreeNode *tmpnode;
    queue<BPTreeNode*>q;
    if(tmp != NULL){
        q.push(tmp);
    }
    int usedchild = 0,nextchild = 0,itchild = 0;
    while(!q.empty()){
        tmp = q.front();
        q.pop();
        //输出值
        //计算自己的孩子个数，计算用了前面孩子的个数
        //是否达到前面孩子个数，
        //没有达到就把自己的孩子加到nextchildnum，表示下一层的孩子个数，后面赋值用
        //前面孩子的个数达到了，说明一层完结了，输出回车。
        //把nextchildnum 作为用来比较的个数。下一层迭代继续
        if(tmp == Tree){
            //直接输出 写成函数不懂吗，，老是搞这么大代码
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
            if(!tmp->Isleaf)cout << '\n';
            usedchild = 0;
            nextchild=0;
            childnum = tmp->key_num+1;
            //孩子入队
            for(i = 0;i < tmp->key_num+1;i++){
                if(tmp->child[0] == NULL)break;
                q.push(tmp->child[i]);
            }   
        }
        else{
            itchild = tmp->key_num+1;
            usedchild += 1;
            nextchild += itchild;
            //直接输出
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
            //孩子入队
            for(i = 0;i < tmp->key_num+1;i++){
                if(tmp->child[0] == NULL)break;
                q.push(tmp->child[i]);
            }         
            if(usedchild == childnum){
                cout << '\n';
                usedchild = 0;
                childnum = nextchild;
            }   
        }
    }
}