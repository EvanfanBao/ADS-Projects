#include<iostream>
#include<vector>
using namespace std;
// class Solution {
// public:
//     int findLengthOfLCIS(vector<int>& nums) {
//         int n = nums.size();
//         int lcis[n][n];
//         int k,i,j;
//         for( i = 0;i < n;i++)
//             lcis[i][i] = 0;
//         for( k = 1;k < n;k++)
//             for( i = 0;i < n;i++){
//                 j = i+k;
//                 if(nums[j] > nums[j-1])lcis[i][j] = lcis[i][j-1]+1;
//                 else lcis[i][j] = lcis[i][j-1];
//         }
//          return lcis[0][n-1];
//     }
// };

// class Solution {
// public:
//     int findLengthOfLCIS(vector<int>& nums) {
//         int n = nums.size();
//         int lcis[n];
//         int k,i,j;
//         lcis[0] = 1;
        
//         for(int i = 1;i < n;i++){
//             if(nums[i] > nums[i-1])lcis[i] = lcis[i-1]+1;
//             else lcis[i] = 1;
//         }
//         int max = -1;
//         for(int i = 0;i < n;i++)
//             if(lcis[i] > max)max = lcis[i];

//         return max;
//     }
// };

class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        int count = 1;
        int k,i,j;
        int max = 1;
        if(n==0)max=0;
        for(int i = 1;i < n;i++){
            if(nums[i] > nums[i-1]){
                count++;
                if(count >= max)max = count;
                }
            else count = 1;
        }
        return max;
    }
};


int main(){
    vector<int> nums(5);
    for(int i=0; i < 5;i++)
        cin >> nums[i];
    int res;Solution x;
    res = x.findLengthOfLCIS(nums);
    cout << res;
}