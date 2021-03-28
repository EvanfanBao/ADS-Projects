#include<iostream>

using namespace std;


// 极其简单的一维dp--并无思维含量
int main()
{
    int n;
    cin >> n;
    int *house = new int[n];
    int *money = new int [n];
    for(int i;i < n;i++)
        cin >> house[i];

    money[0] = house[0];
    money[1] = max(house[0],house[1]);
    for(int i = 2;i < n;i++)
        money[i] = max(house[i] + money[i-2],money[i-1]);
    cout << money[n-1];
}   