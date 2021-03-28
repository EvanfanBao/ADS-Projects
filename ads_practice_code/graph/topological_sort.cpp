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
    bool addEdge(int v1,int v2){
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
};

void Graph::EvalOutdegree(){
    for(int i = 0; i < vertices.size();i++)
        Outdegree[i] = vertices[i].connectors.size();
}

void Graph::EvalIndegree(){
    for(int i = 0; i < reverse_vertices.size();i++)
        Indegree[i] = reverse_vertices[i].connectors.size();
}


void Graph::Topological_sort(const Graph& gp,vector<int>& TopNum){
    TopNum.resize(gp.nVertex);      // resize
    int counter(0);                 // order start from 0
    int i;
    vector<bool>check(gp.nVertex,false);    // see if vertices of indegree 0 is checked
    vector<int> temp_Indegree(gp.Indegree); // temp indegree in case of change the original data
    for(counter; counter < gp.nVertex;counter++){
        for(i = 0;i < gp.nVertex;i++){          // find the unchecked vertice of indegree 0
            if(!check[i] && temp_Indegree[i] == 0){
                break;
            }
        }
        if(i == gp.nVertex){        // cycle
            cerr << "graph has a cycle";return;
        }
        check[i] = true;            //checked 
        TopNum[i] = counter;        //order
        for(auto adjV : gp.vertices[i].connectors)      //update indegree
            temp_Indegree[adjV]--; 
    }   
}


// improvement -- keep all the unsiged vertices of degree in a special box---queue or stack
// 事实上 container都可以---vector都行--c++的强大
// 这里我用的 deque 当作stack用
void Graph::Topological_sort_2(const Graph& gp,vector<int>& TopNum){
    deque<int> ZeroIndegree;
    TopNum.resize(gp.nVertex);      // resize
    int counter(0);                 // order start from 0
    int i;
    vector<int> temp_Indegree(gp.Indegree); 
    for( i = 0;i < gp.nVertex;i++)      //顶点是从0开始到v-1
        if(temp_Indegree[i] == 0)ZeroIndegree.push_back(temp_Indegree[i]);
    while(!ZeroIndegree.size()){
        i = ZeroIndegree.back();
        ZeroIndegree.pop_back();
        TopNum[i] = counter++;
        for(auto adjV : gp.vertices[i].connectors)      //update indegree
            if(--temp_Indegree[adjV] == 0)ZeroIndegree.push_back(adjV); 
    }
    if(counter != gp.nVertex)
        cerr << "graph has a cycyle";
    return;
    
}


int main(){
    int v,e;
    //cin >> v >> e;
    Graph gp(4,4,true);
    vector<int> topnum;
    // gp.addEdge(0,1);
    // gp.addEdge(0,2);
    // gp.addEdge(1,3);
    // gp.addEdge(2,3);
    // gp.addEdge(1,4);
    // gp.addEdge(2,5);
    // gp.addEdge(4,6);
    // gp.addEdge(5,6);
    gp.addEdge(3,1);
    gp.addEdge(3,2);
    gp.addEdge(1,0);
    gp.addEdge(2,0);
    gp.EvalIndegree();
    gp.EvalOutdegree();
    // for(int i = 0; i < 4;i++)
    // {   //cout << gp.reverse_vertices[i].connectors.size();
    //     cout << " " << gp.Outdegree[i];
    // }
    Graph::Topological_sort(gp,topnum);
    for(int i = 0; i < 4;i++){
        cout << topnum[i];
    }
}