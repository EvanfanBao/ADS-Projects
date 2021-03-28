#include<iostream>
#include<vector>

using namespace std;

#define LEAST -1000


int Interview(int candidate){
    return candidate % 3;      // simple quality calculation
}

int Hiring(int N){
    int Best = 0;       // candidate 0 is best---dummy---least qualified
    int BestQ = LEAST;  // candidate 0's quality
    int Qi;
    for(int i = 1; i <= N;i++){
        Qi = Interview(i);
        if(Qi > BestQ){
            BestQ = Qi;
            Best = i;
            //hire(i)
        }
    }
    return Best;        //返回做好的quality的--那就是我们真正要雇佣的---题目描述是一个人 
}