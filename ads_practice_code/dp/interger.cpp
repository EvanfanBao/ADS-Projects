#include<iostream>
#include<vector>

using namespace std;
//应该没错 但是leetcode 超出时间限制了 太难了

void tobinary(int n,vector<int>& bin){
    int i(0);
    while(n/2 != 0){
        bin[i] = n%2;
        i++;
        n = n/2;
    }
    bin[i] = 1;
} 

int main()
{   
    vector<int> bin(32);
    bin.assign(32,0);
    int n;cin >> n;
    bool flag = false;
    //tobinary(n,bin);
    int count(0);
    tobinary(n,bin);
    // for(int i = 0;i <= n;i++){
    //     flag = false;
    //     bin.assign(32,0);
        
    //     tobinary(i,bin);
    //     for(int j = 1;j < 32;j++){
            
    //         if(bin[j]==1 && bin[j-1]==1){
    //             flag = true;break;
    //         }
    //     }
    //     if(flag == false)count++;
    // }
    //cout << count;
    
	return 0;
}