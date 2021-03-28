#include<iostream>
#include<vector>

using namespace std;

const int CAPACITY = 100;

//每次都往最后一个放 放不下就开一个新的 --假定容器大小为100--item为0-100的整数 返回需要箱子的个数
//近似解小于最优解2倍。<= 2M-1
int NextFit(vector<int> items){
    int n = items.size();
    vector<int> bins;
    if(n == 0)return 0;
    bins.push_back(items[0]);
    for(int i = 1; i < n;i++){
        if(bins.back() + items[i] <= CAPACITY)
            *(bins.rbegin()) = bins.back() + items[i];
        else 
            bins.push_back(items[i]);
    }
    //cout << *(bins.rbegin());
    return bins.size();
}

//从前往后找 找第一个能放下的 就塞进去 都塞不进 就开一个新的--假定条件相同
//O(NlogN) 近似解小于等于最优解 1.7 倍
int FirstFit(vector<int> items){
    int n = items.size();
    vector<int> bins;
    if(n==0)return 0;
    bins.push_back(items[0]);
    int i,j;
    for( i = 1;i < n;i++){
        for( j = 0; j < bins.size();j++)
            if(bins[j] + items[i] <= CAPACITY){
                bins[j] += items[i];
                break;
            }
        if(j == bins.size())
            bins.push_back(items[i]);
    }
    return bins.size();
}


//从前向后 找空间剩余最少的 近似解小于等于最优解1.7倍 类似firstfit
int BestFit(vector<int> items){
    int n = items.size();
    vector<int> bins;
    if(n==0)return 0;   //没有物品
    bins.push_back(items[0]);
    int i,j;int Ind;
    for(i = 1;i < n;i++ ){
        Ind = -1;
        for(j = 0; j < bins.size();j++){
            if(bins[j] + items[i] <= CAPACITY){
                if(Ind == -1)Ind = j;        //满足条件的j里面 从设第一个为最大
                if(bins[j] > bins[Ind]) Ind = j;
            }
        }
        if(Ind == -1)bins.push_back(items[i]);
        else bins[Ind] += items[i];
    }
    return bins.size();
}

int WorstFit(vector<int> items){
    int n = items.size();
    vector<int> bins;
    if(n==0)return 0;   //没有物品
    bins.push_back(items[0]);
    int i,j;int Ind;
    for(i = 1;i < n;i++){
        Ind = 0;
        for(j = 0; j < bins.size();j++){
            if(bins[j] < bins[Ind])Ind = j;
        }
        if(bins[j] + items[i] <= CAPACITY)bins[j] += items[i];
        else bins.push_back(items[i]);
    }
    return bins.size();
}


int main(){
    vector<int> items;
    int n;
    cin >> n;int tmp;
    for(int i = 0;i < n;i++){
        cin >> tmp;items.push_back(tmp);
    }
    int res = FirstFit(items);
    cout << res;
}

