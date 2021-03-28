#include<iostream>
using namespace std;
//图的邻接表存储
#define MAX_VERTEX_NUM 20

struct ArcNode{
    ArcNode(int a,int w):adjvex(a),weight(w),nextarc(NULL){}
    ArcNode():nextarc(NULL){};
    int adjvex;         //边指向的顶点
    int weight;         //这条边本身的权重
    ArcNode *nextarc;   //指向下一条指针---邻接表--链表将同一个结点的不同连接的边串起来
};

//结点
struct VNode{
    VNode():key(0),firstarc(NULL){}
    int key;            //顶点本身的值
    ArcNode *firstarc;  //邻接表的第一条边---注意指向的就是边的邻接表的结构了，和顶点本身的结构还是不太一样的
};
typedef VNode AdjList[MAX_VERTEX_NUM];

class Graph{
public:
    Graph();
    ~Graph();
private:
    AdjList vertices;   //图的邻接表 数组
    int vexnum,arcnum;  //顶点数和边数
public:
    void BuildGraph();
private:
    void InsertEdge(int i,int a,int w);
};

Graph::Graph():vexnum(0),arcnum(0)
{
    for(int i = 0;i < MAX_VERTEX_NUM;i++){
        vertices[i].key = 01;
        vertices[i].firstarc = NULL;
    }
}
Graph::~Graph(){}

void Graph::BuildGraph(){
    cout << "输入顶点的个数" << endl;
    cin >> vexnum;
    cout << "输入弧的个数" << endl;
    cin >> arcnum;
    for (int i = 0; i < vexnum; i++){
        cout << "输入第" << i + 1 << "个顶点的数据及边数" << endl;
        cin >> vertices[i].key;
        int single_arc_num = 0;
        cin >> single_arc_num;
        for (int j = 0; j < single_arc_num; j++){
            cout << "输入第" << i + 1 << "个顶点相邻的表节点的顶点位置以及权值" << endl;
            int a = 0, w = 0;
            cin >> a >> w;
            InsertEdge(i, a, w);
        }
    }
}


void Graph::InsertEdge(int i, int a, int w){
    //新建一个表节点
    ArcNode *end = new ArcNode(a, w);
    //将第i个单链表移动到表尾
    ArcNode *temp = vertices[i].firstarc;
    if (!temp){
        vertices[i].firstarc = end;
        return;
    }
    while (temp){
        temp = temp->nextarc;
    }
    //在尾部插入该表节点
    temp = end;
}


int main(){
    Graph gra;
    gra.BuildGraph();
    
    cout << endl;
    return 0;

}