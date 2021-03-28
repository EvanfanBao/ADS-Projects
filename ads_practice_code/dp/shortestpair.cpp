#include<iostream>


using namespace std;
const int V = 4; // number of vertices, starting from 0 to N 0-1-2----9
const int Infinity = 1000;
void AllPairs(int AdjMax[][V],int D[][V], int V)
{
    int i,j,k,l;
    // copy the cost. D-1
    for( i = 0;i < V; i++)
        for(int j = 0;j < V;j++)
            D[i][j] = AdjMax[i][j];
    for(k = 0;k < V;k++)
        for(i = 0;i < V;i++)  // for all pairs i j 
            for(j = 0;j < V;j++){   //direction, so j strat from 0
                if(D[i][k]+D[k][j] < D[i][j])
                    D[i][j] = D[i][k]+D[k][j];
            }
    cout << D[3][2];
}


int main(){
    int AdjMax[V][V];int D[V][V] = {0};
    AdjMax[0][0] = Infinity;AdjMax[0][1] = 5; AdjMax[0][2] = 1;AdjMax[0][3] = 2;
    AdjMax[1][0] = 2;AdjMax[1][1] = Infinity;AdjMax[1][2] = Infinity;AdjMax[1][3] = Infinity;
    AdjMax[2][0] = Infinity;AdjMax[2][1] = 6;AdjMax[2][2] = Infinity;AdjMax[2][3] = 2;
    AdjMax[3][0] = Infinity;AdjMax[3][1] = Infinity;AdjMax[3][2] = Infinity;AdjMax[3][3] = Infinity;
    AllPairs(AdjMax,D,V);
}