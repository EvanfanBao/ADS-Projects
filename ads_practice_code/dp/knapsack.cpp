#include<iostream>
#include<queue>

using namespace std;
// fractional version
// get the maxmium total profit sigma(pi * xi);
// under the constraint sigma(wi * xi) <= M

// M--capacity  w[]weight p[]profit N number of items
// greedy -- choose the one with manximum profit density

class item{
public:
    int weight;
    int profit;
    double profit_density;
    item(int _weight,int _profit):weight(_weight),profit(_profit),profit_density(profit*1.0/weight){}
    item(){}
    ~item(){}
    bool operator<(const item& rhs){
        return profit_density < rhs.profit_density;
        }
    bool operator>(const item& rhs){
        return profit_density > rhs.profit_density;
        }
};

double fraction_knapsack(int M,vector<item> items){
    priority_queue< item > pq;
    // for(auto i : items)
    //     pq.push(i);
    // item tem_item;
    // double totalWeight = 0;
    // double totalProfit = 0;
    // while(1){
    //     tem_item = pq.top();
    //     if(totalWeight + tem_item.weight <= M){
    //         totalWeight += tem_item.weight;
    //         totalProfit += tem_item.profit;
    //         pq.pop();
    //     }
    //     else{
    //         double res = M-totalWeight;
    //         totalWeight = M;
    //         totalProfit += tem_item.profit_density * res;
    //         break;
    //     }
    // }
    // return totalProfit;
}

int main(){
    vector<item> items;
    
    int weight,profit;
    for(int i = 0;i < 3;i++){
        cin >> weight >> profit;
        item read_item(weight,profit);
        items.push_back(read_item);
    }
    double result = fraction_knapsack(20,items);
    cout << result;
}  