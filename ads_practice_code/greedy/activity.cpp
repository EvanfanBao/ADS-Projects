#include<iostream>
#include<string>

using namespace std;
// 活动选择问题例程
// 最早结束时间排序
// greedy选择最早结束时间
// 同时满足约束条件
// O(NLOGN)

int activity_select(int S[], int F[],int c[],int N){
    
    c[0] = 0;int j = 1;
    for(int i = 1;i < N;i++){
        if(S[i] >= F[c[j-1]])
            c[j++] = i;
    }
    return j;
}

/*
int activity_dp(int S[],int F[],int c[],int N){
    int cmp[N][N];
    int i,j,k,l;
    int max;
    //cmpij -- 第i个活动结束(从i+1活动开始包含)到第j个活动开始以前(j-1个活动包含)
    for(i = 0;i < N;i++)
        for(j = 0;j <= i+1;j++)
            cmp[i][j] = 0;           
    for(i = 0;i < N;i++)
        cmp[i][i+2] = 1;

    for(k = 1;k < N;k++)             //间隔
        for(i = 0;i < N-k;i++){
            j = i + k;
            for(l = i+1;l < j;l++){
                if(cmp[i][l]+cmp[l][j] + 1 > max ) 
                    max = cmp[i][l]+cmp[l][j] + 1;
            }
            cmp[i][j] = max;
        }
}
*/


int FindK(int S[],int F[],int j){
    for(int i = j-1;i >= 0;i--){
        if(F[i] <= S[j])
            return i;
    }
    return -1;
}
//也是按最早结束时间排序 --- 没问题
int activity_dp2(int S[], int F[],int c[],int N){
    int i,j,k;
    int optact[N][N];
    optact[0][0] = 1;
    int m1,m2;
    for(j = 1;j < N;j++){
        m1 = optact[0][j-1];
        k = FindK(S,F,j);
        if(k == -1)m2 = 0;
        else m2 = optact[0][k] + 1;
        optact[0][j] = m1 > m2 ? m1:m2;
    }
    return optact[0][N-1];
}

//权重版本
int activity_dpweight(int S[], int F[],int c[],int N,int Weight[]){
    int i,j,k;
    int optact[N][N];
    optact[0][0] = 1;
    int m1,m2;
    for(j = 1;j < N;j++){
        m1 = optact[0][j-1];
        k = FindK(S,F,j);
        if(k == -1)m2 = 0;
        else m2 = optact[0][k] + Weight[j];
        optact[0][j] = m1 > m2 ? m1:m2;
    }
    return optact[0][N-1];
}


int main(){
    int S[11] = {1,3,0,5,3,5,6,8,8,2,12};
    int F[11] = {4,5,6,7,9,9,10,11,12,14,16};
    int c[11];
    //int num = activity_select(S,F,c,11);
    int num = activity_dp2(S,F,c,11);

    // cout << "S sequence is " << endl;
    // for(int i = 0; i < num;i++)
    //     cout << S[c[i]] << " ";
    // cout << "\n"<< "F sequence is " << endl;
    // for(int i = 0; i < num;i++)
    //     cout << F[c[i]] << " ";
    cout << num;
}