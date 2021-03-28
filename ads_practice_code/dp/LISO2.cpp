#include<iostream>
#include<string.h>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

void LCS(string X, string Y )
{
    int n = X.size(), m = Y.size();
    int size1, size2;
    int i,j;
    string lcs[n+1][m+1];    // X0="" X1="x1" ... Xn="x1 x2 ... xn" = X
    for(i = 0;i <= m;i++)
        lcs[0][i] = "";      //X0 is null Y0 is null. their lcs is null with other sequences
    for(i = 0;i <= n;i++)
        lcs[i][0] = "";
    for(i = 0; i < n;i++)
        for(j = 0; j < m;j++)
        {
            if(X.substr(i,1) == Y.substr(j,1))
                lcs[i+1][j+1] = lcs[i][j] + X.substr(i,1);
            else{
                size1 = lcs[i+1][j].size();size2 = lcs[i][j+1].size();
                lcs[i+1][j+1] =  size1 > size2 ? lcs[i+1][j] : lcs[i][j+1];
            }
        }
    cout << lcs[n][m];
}

void vector_to_string(const vector<int>& arr,string& str)
{
    str = "";
    for(int i = 0; i < arr.size();i++)
    {
        str += to_string(arr[i]);
    }
}

//fail
void LIS(const vector<int>& arr)
{
    vector<int> arr_sorted = arr;
    sort(arr_sorted.begin(),arr_sorted.end());
    string str_original,str_sorted;
    vector_to_string(arr_sorted,str_sorted);
    vector_to_string(arr,str_original);
    LCS(str_original,str_sorted);
}

int main()
{
    vector<int> arr;
    int value;
    for(int i = 0;i < 5;i++)
    {
        cin >> value;
        arr.push_back(value);
    }
    LIS(arr);
}

