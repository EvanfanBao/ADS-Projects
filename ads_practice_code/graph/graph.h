#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

struct Vertex{
    int key;
    vector<int> connectors;     //当前邻接的所有顶点--其实就和邻接表很像了，但是动态增长的 空间没有浪费
    
};

//无向图用 邻接表 互相指表示--有向图-只有一边指
struct Graph{
    vector<Vertex> vertices;
    vector<int> weight;
    vector<int>Indegree;
    vector<int>Outdegree;
    vector<Vertex>reverse_vertices; //反向邻接表
    int nVertex;
    int nEdge;
    bool IsDG;
    //Constructor
    Graph(int v,int e,bool _IsDG=false):nVertex(v),nEdge(e),IsDG(_IsDG){vertices.resize(v);Indegree.resize(v);Outdegree.resize(v);reverse_vertices.resize(v);}
    Graph(){}
    void EvalIndegree();
    void EvalOutdegree();

    //根据顶点数字值添加边
    bool addEdge(int v1,int v2,int weight = 1){
        if(max(v1,v2) > vertices.size())return false; //out of bound
        if(IsDG){
            vertices[v1].connectors.push_back(v2);
            
            reverse_vertices[v2].connectors.push_back(v1);      //反向邻接表 v1指向v2。v2被v1指向
        }
        else{
            vertices[v1].connectors.push_back(v2);
            vertices[v2].connectors.push_back(v1);
        }
        return true;
    }
    static void Topological_sort(const Graph& gp,vector<int>& TopNum);
    static void Topological_sort_2(const Graph& gp,vector<int>& TopNum);
    static void Prim(const Graph& gp);
};

