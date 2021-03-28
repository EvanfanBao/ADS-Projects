#include"graph.h"


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


//
void Graph::Prim(const Graph& gp){

}

