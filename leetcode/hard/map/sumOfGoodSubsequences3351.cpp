/**
 * @Time : 2024/11/12-11:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    /*
     * 以nums[i]为结尾的子序列 前面的子序列以nums[i] - 1， nums[i] + 1结尾
     * 并且还需要这些序列总共有多少个 以及原本的和是多少
     * 因为能组成的新子序列的和包括2部分：
     * 1. 除nums[i]之前的部分 也就是原本的和
     * 2. 以及nums[i]贡献的，这部分为nums[i] * c, 其中c为以nums[i]为结尾的序列的和
     * hash表记数
     */
    int sumOfGoodSubsequences(vector<int>& nums) {
        ll ans = 0, mod = 1e9 + 7;
        unordered_map<int, ll> sum, cnt;
        for(int num : nums) {
            ll c1 = cnt[num - 1], c2 = cnt[num + 1], c = c1 + c2 + 1;
            ll new_sum = (c * num % mod + sum[num - 1] + sum[num + 1]) % mod;
            ans = (ans + new_sum) % mod;
            cnt[num] = (cnt[num] + c) % mod;
            sum[num] = (sum[num] + new_sum) % mod;
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}