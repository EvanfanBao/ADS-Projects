#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

using namespace std;
struct station{
    float price;
    int dist;
    bool operator<(const station& sta){return dist < sta.dist;}
    bool operator>(const station& sta){return dist > sta.dist;}
};
int main(){
    int Cmax,D,Davg,N;
    station stat;
    cin >> Cmax >> D >> Davg >> N;
    vector<station> stations;
    
    for(int i = 0;i < N;i++){
        cin >> stat.price >> stat.dist;
        stations.push_back(stat);
    }
    stat.price = 0;stat.dist = D;
    stations.push_back(stat);       //目的地 也看成车站

    sort(stations.begin(),stations.end());
    if(stations[0].dist != 0){
        cout << "The maximum travel distance = 0.00";
        return 0;
    }
    

    float traveldist(0),maxdist(0),currentprice(0), totalprice(0),minprice(1000),nowGas(0);
    int minindex(0);
    int nextSta;bool flag = false;

    currentprice = stations[0].price;   //初始位置
    
    for(int j = 0; j < N;j = nextSta){     //j表示当前的车站----其实traveldist就可以直接表示的--都一样吧    
        maxdist = traveldist + Cmax * Davg; ////已经经过的距离 + 上如果充满油能达到的最大距离 = 能达到的最大距离
        minindex = j+1;
        minprice = 10000;
        for(int i = j+1;i <= N;i++)            //遍历所有车站
        {  
            if(stations[i].dist <= maxdist && stations[i].dist > traveldist)    //表示在能达到范围内的车站 
                if(stations[i].price < minprice){               
                    minprice = stations[i].price;               
                    minindex = i;
                    if(minprice < currentprice)break;       //前面尽量找小的--但遇到比当前小的直接走
                }   
        }
        if(minprice == 10000){
            printf("The maximum travel distance = %.2f",maxdist);return 0;
        }
        //如果钱更小 刚好加油到那个地方去--直接转移过去就行了
        if(minprice < currentprice){
            totalprice += ((stations[minindex].dist-traveldist)/Davg - nowGas) *currentprice;
            nowGas = 0;     //到达了下一个点的油--直接在这里算
        }
            //如果钱相对多，那么我这一次先冲满
        else{
            totalprice += (Cmax-nowGas) * currentprice;
            nowGas = Cmax - (stations[minindex].dist-traveldist)/Davg;      //下一次的nowgas
        }
        nextSta = minindex;
        traveldist = stations[minindex].dist;
        currentprice = stations[minindex].price;
        
    }
    
    printf("%.2f",totalprice);
    
}