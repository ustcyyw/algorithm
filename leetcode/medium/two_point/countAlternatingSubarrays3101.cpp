/**
 * @Time : 2024/4/1-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛391 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long countAlternatingSubarrays(vector<int>& nums) {
        long long n = nums.size(), ans = 0;
        for(int i = 0, j = 0; i < n; ) {
            j = i + 1;
            while(j < n && nums[j] != nums[j - 1]) j++;
            long long t = j - i;
            ans += t * (t + 1) / 2;
            i = j;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}