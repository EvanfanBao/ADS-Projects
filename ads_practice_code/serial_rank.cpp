#include<iostream>
using namespace std;

void Serial_Rank(int A[],int B[],int N,int RankA[],int RankB[]){
    int i,j;
    i = j = 0;
    while(i <= N || j <= N){
        if(A[i + 1] < B[j + 1])
            RankB[++i] = j;
        else{
            RankA[++j] = i;
            cout << RankA[1];
        }
    }
   
}
int main(){
    int A[6] = {0,11,12,15,17,1000};
    int B[6] = {0,13,14,16,18,1000};
    int RankA[] = {0};
    int RankB[] = {0};
    Serial_Rank(A,B,4,RankA,RankB);
    for(int i = 1; i < 5;i++)
    {
        //cout << RankA[i] << endl;
        
    }
}