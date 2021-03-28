#include<iostream>

using namespace std;


// 基本思想和前面一样 把圆成两部分，用robbery1同样的方法=就能求出
int main()
{
    int n;
    cin >> n;
    int *house = new int[n];
    int *money = new int [n];
    for(int i;i < n;i++)
        cin >> house[i];
    int temp;
    if(n==0){cout << 0;return 0;}
    if(n==1){cout << house[0];return 0;}
    if(n==2){cout << max(house[0],house[1]);return 0;}
    if(n==3){temp = max(house[0],house[1]); cout << max(temp,house[2]); return 0;}
    money[0] = house[0];
    money[1] = max(house[0],house[1]);

    for(int i = 2;i < n-1;i++)      //第一个可能选最后一个不选
        money[i] = max(house[i] + money[i-2],money[i-1]);
    int max1 = money[n-2];
    
    money[1] = house[1];
    money[2] = max(house[1],house[2]);
    for(int i = 3;i < n;i++){
        //cout << money[i];
        money[i] = max(house[i] + money[i-2],money[i-1]);
        //cout << money[i-2];
    }
    int max2 = money[n-1];
    
    if(max1 > max2)cout << max1;
    else cout << max2;
}   