#include<iostream>
#include<string.h>
#include<string>

using namespace std;

int LCS(string X, string Y )
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
    return lcs[n][m].size();
    //cout << lcs[n][m];
}

//fail
void Palindrome(const string& str)
{
    int n = str.size();
    int max = 0;
    int temp;
    for(int i = 0 ; i < n;i++)
    {
        temp = LCS(str.substr(0,i),str.substr(i,n-i-1));
        if(temp > max)max = temp;
    }
    cout << max;
}

int main(){
// string X = "ABBAC";
// string Y = "ABBAC";
// LCS(X,Y);
    string str("racecar");
    Palindrome(str);
}


