#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
// fractional version----greedy algorithm --- precise optimal solution
// greedy choice == find the maximum profit density pi/wi --- 最高性价比 
// 总容量M 体积为wi--也可以理解为总承重M 每个item重量wi
// 浮点数--还是让人很不舒服的
// 代码组织一般---思想正确
// 用优先队列可以快很多---但不太好组织

int maxInd(vector<double>& ppw,vector<int>& check){
    int ind(0);
    int i;
    for(i = 0;i < ppw.size();i++)
        if(check[i] != 1)break;
    ind = i;
    for(i = 0; i < ppw.size();i++)
        if(!check[i] && ppw[i] > ppw[ind])ind = i;
    check[ind] = 1;
    return ind;
}


template <typename T>
T** new_Array2D(int row,int col)
{
    int size = sizeof(T);
    int point_size = sizeof(T*);
    T **arr = (T**)malloc(point_size * row + size * row * col);
    if(arr != NULL)
    {
        T *head = (T*)((int)arr + point_size * row);
        for(int i = 0;i < row;++i)
        {
            arr[i] = (T*)((int)head + i * col * size);
            for(int j = 0;j < col;++j)
                new(&arr[i][j]) T;
        }
    }
    return (T**)arr;
}

template <typename T>
void delete_Array2D(T **arr,int row, int col)
{
    for(int i = 0;i < row;++i)
        for(int j = 0;j < col;++j)
            arr[i][j].~T();
    if(arr != NULL)
        free((void**)arr);
}


double KnapSack_fra(double M,vector<int> weight,vector<int> price){
    int n = weight.size();
    vector<double> ppw;    //price per weight
    vector<int>check(n,0);
    
    double tmp;
    for(int i = 0;i < n;i++){
        tmp = (double)price[i] / weight[i];             //计算性价比
        ppw.push_back(tmp);
    }
    double total_price(0);
    double total_weight(0);
    int maxind;
    
    //每次计算就把最高性价比的加上去。如果超过了，那就努力的用最高性价比的东西填满--计算差值加上去即可
    for(int i = 0; i < n;i++){
        maxind = maxInd(ppw,check);
        //cout << maxind;
        total_price += price[maxind];
        total_weight += weight[maxind];
        //cout << total_price << " ";
        if(total_weight > M){
            total_price -= price[maxind];
            total_weight -= weight[maxind];
            total_price += price[maxind] * ((M-total_weight)/weight[maxind]);
            
            break;
        }
    }
    return total_price;
}

#define MAXSIZE 10
double knapsack_dp(double M,vector<int> weight,vector<int> price){
    int n = weight.size();
    int **p = new_Array2D<int>(n+1,(int)M+1);
    for(int i = 0;i <= M;i++)
        p[0][i] = 0;
    for(int i = 1;i <= n;i++){
        p[i][0] = 0;
        for(int w = 1;w <= M;w++){
            if(weight[i] <= w){
                if(price[i]+p[i-1][w-weight[i]])
                    p[i][w] = price[i] + p[i-1][w-weight[i]];
                else 
                    p[i][w] = c[i-1][w];
            }
            else
                p[i][w] = p[i-1][w];
        }
    }
    int maxp = p[n][(int)M];
    delete_Array2D(p,n+1,M+1);
    return maxp;
}   


int main(){
    vector<int> weight;
    vector<int> price;
    int n;
    cin >> n;   // read data number
    double M;   
    int tw,tp;
    cin >> M;   // capacity
    for(int i = 0; i < n;i++)
    {
        cin >> tw >> tp;
        weight.push_back(tw);
        price.push_back(tp);
    }
    
    double res(0);
    res = KnapSack_fra(M,weight,price);
    cout << res;   
}