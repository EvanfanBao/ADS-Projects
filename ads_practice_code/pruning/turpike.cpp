//The Turnpike Reconstruction Problem
//according to the code in the slides.
#include<iostream>
#include<stdio.h>
#include<set>

using namespace std;


typedef multiset<int> DistSet;
typedef int DisType;

bool Reconstruct(DisType *X,DistSet& D,int N,int left, int right);
void Delete(DisType x,DistSet& D);
bool Check(DisType *X, DistSet& D,int Max,int N,int left, int right);

int main(){
    DistSet D;
    bool success;
    D.insert({1, 2, 2, 2, 3, 3, 3, 4, 5, 5, 5, 6, 7, 8, 10 });
    //6 * 5 / 2 = 15;; N = 6
    DisType *X = new DisType[7]; // use 1 - 6 
    X[1] = 0; X[6] = *(D.rbegin());
    D.erase(--D.end());
    success = Reconstruct(X,D,6,2,5);
    if(success)
        for(int i = 1; i <= 6; i++){
            cout << X[i] <<' ';
        }
}



bool Reconstruct(DisType *X,DistSet& D,int N,int left, int right){
    bool Found = false;
    bool OK;
    DisType CurMax;
    if(D.empty())
        return true; //done
    CurMax = *(D.rbegin()); //max
    OK = Check(X,D,CurMax,N,left,right);
    if(OK){
        X[right] = CurMax;
        for(int i = 1; i < left;i++)Delete(CurMax-X[i],D);
        for(int i = right+1; i <= N;i++)Delete(X[i]-CurMax,D);
        Found = Reconstruct(X,D,N,left,right-1);
        if(!Found){
            for(int i = 1; i < left;i++)D.insert(X[right]-X[i]);
            for(int i = right+1; i <= N;i++)D.insert(X[i]-X[right]);
        }  
    }
    if(!Found){
        OK = Check(X,D,X[N]-CurMax,N,left,right);
        if(OK){
            X[left] = X[N]-CurMax;
            for(int i = 1; i < left;i++)Delete(X[left]-X[i],D);
            for(int i = right+1; i <= N;i++)Delete(X[i]-X[left],D);
            Found = Reconstruct(X,D,N,left+1,right);
            if(!Found){
                for(int i = 1; i < left;i++)D.insert(X[left]-X[i]);
                for(int i = right+1; i <= N;i++)D.insert(X[i]-X[left]);
            }
        }
    }
    return Found;
}


void Delete(DisType x,DistSet& D){
    DistSet::iterator it;
    it = D.find(x);
    D.erase(it);
}


bool Check(DisType *X, DistSet& D,int Max,int N,int left, int right){
    int count[11] = {0};  //这里是10 X[N]
    int i;
    for( i = 1; i < left;i++){
        count[Max-X[i]]++;
    }
    for( i = N;i > right;i--){
        count[X[i]-Max]++;
    }
    for( i = 0;i < *(D.rbegin());i++){
        if(count[i] > D.count(i))break;
    }
    if(i < *(D.rbegin()))
        return false;
    else
        return true;
}
