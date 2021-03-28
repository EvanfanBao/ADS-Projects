#include<iostream>

using namespace std;

// 切棒问题例程--参考算法导论
// 状态转移--采用较为简单方式--选择一部分保留--另一部分切--找max

void Cut_Rod(int price[],int n)
{
    int revenue[n+1];   // start from 1----or 0' price is 0
    revenue[0] = 0;
    int q;
    for(int j = 1;j <= n;j++){      //rod 长度
        q = -1000;
        for(int i = 1;i <= j;i++)  //切割情况
            if(q < (price[i] + revenue[j - i]))
                q = price[i] + revenue[j-i];
        revenue[j]  = q;
    }
    for(int i = 1;i <= n;i++)
        cout << revenue[i] << " ";
}

int main(){

    int price[100];
    int n = 10;
    for(int i = 1; i <= 10;i++)
        cin >> price[i];
    Cut_Rod(price,10);

}