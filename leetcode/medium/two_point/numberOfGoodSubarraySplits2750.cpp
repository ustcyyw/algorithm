/**
 * @Time : 2023/7/14-5:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    int numberOfGoodSubarraySplits(vector<int>& nums) {
        long long res = 0;
        for(int i = 0, lo = -1, hi = -1; i < nums.size(); i++) {
            if(nums[i] == 1) {
                if(res == 0) res = 1;
                hi = i;
                if(lo != -1) res = res * (hi - lo) % mod;
                lo = hi;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}