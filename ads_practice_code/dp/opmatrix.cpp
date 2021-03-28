#include<iostream>
#include<vector>

using namespace std;
const int Infinity = 10000;
//calculate the optimal cost of n matrice multiplication
int OptMax(int r[],int N ){
    int m[N+1][N+1];        //N matrices multiplication  --- m[i][i] = 0; start from 1
    int cost,j;
    int i,k,l;
    for( i = 1; i <= N;i++)m[i][i] = 0;   // record the cost===but don't record the ordering!!! how to implement??
    for( k = 1;k < N;k++)        //i+k = j
        for( i = 1; i+k <= N;i++){
            j = i+k;m[i][j]= Infinity;
            for( l = i;l < j;l++){
                cost = m[i][l] + m[l+1][j] + r[i-1]*r[l]*r[j];
                if(cost < m[i][j])m[i][j] = cost;
            }
        }
        return m[1][N];
}

//another way to record the status,k Represent start point, i represent the total point
int OptMax_n(int r[],int N){
    int m[N+1][N+1],cost;
    // for(int i = 1; i <= N;i++)m[i][i] = 0;  //m[i][i] = 0;
    // for(int k = 1;k < N;k++)        //k is start
    //     for(int i = 1;i+k <= N;i++){   //i 表示k开始偏移的步数
    //         int j = k+i;m[k][j] = Infinity;
    //         for(int l = k; l < j;l++){
    //             cost = r[i-1]*r[l]*r[j];
    //             if(cost < m[k][j])m[k][j] = cost;
    //         }
    //     }
    // return m[1][N];
    int i,k,l;
    for(k = 1;k < N;k++)
        m[k][0] = 0;
    for(i = 1;i < N;i++)
        for(k = 1;k < N;k++){
            m[k][i] = Infinity;
            for(l = 1;l <= i;l++){
                cost = m[k][l]+m[k+l+1][i-l-1]+r[k-1]*r[k+l]*r[k+i];
                if(cost < m[k][i])
                    m[k][i] = cost;
            }
        }
    return m[1][N-1];
}


int main(){
    int r[5] = {10,20,50,1,100};
    cout << OptMax(r,4) << endl;
    cout << OptMax_n(r,4);
}