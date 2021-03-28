//最长递增子序列---不用连续--返回所有的个数--有一个就返回1个

#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1)return n;
        int* count = new int[n];    //以i为结尾的最大上升子序列的个数
        int* length = new int[n];   //以i为结尾的最大上次子序列的长度
        for(int i = 0;i < n;i++)
        {
            count[i] = 1;
            length[i] = 1;
        }
        for(int j = 0; j < n;j++)
            for(int i = 0; i < j;i++){
                if(nums[i] < nums[j]){
                    if(length[i] >= length[j]){
                        count[j] = count[i];
                        length[j] = length[i]+1;
                    }
                    else if(length[i]+1==length[j]){
                        count[j] += count[i];
                        length[j] = length[i]+1;
                    }
                }
            }
        int max = 0;int res = 0;
        for(int i = 0; i < n;i++)
            if(length[i] > max)max = length[i];
        for(int i = 0;i < n;i++)
            if(length[i] == max)res += count[i];
        
        return res;
    }
    
    
};

int main(){
    vector<int> nums(5);
    for(int i=0; i < 5;i++)
        cin >> nums[i];
    int res;Solution x;
    res = x.findNumberOfLIS(nums);
    cout << res;
}