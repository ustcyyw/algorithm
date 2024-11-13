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

int main() {
    vector<int> arr1 = {1,2,1};
    vector<int> arr3 = {7, 19, 19, 20, 33};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr2 = {"000", "000"};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    s.sumOfGoodSubsequences(arr1);
}
