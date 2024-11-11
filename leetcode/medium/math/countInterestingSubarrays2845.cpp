/**
 * @Time : 2023/9/5-9:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 记a，b分别是是nums[0, j]，nums[0,i] 上满足 num % mod = k 的数的数目 且 i <= j
 * 满足条件的子数组
 * a - b = t, t % mod = k
 * (a - b) % mod = (a % mod - b % mod + mod) % mod = t % mod = k
 * (a % mod - b % mod + mod) % mod = k
 * 因此
 * b % mod = a % mod - k
 * b % mod = a % mod - k + mod
 *
 * 因此，令满足条件num % mod = k的数的数目为sum，可以记录 sum % mod的出现次数
 * 前置去查找 b % mod 的出现次数。
 */
class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        long long res = 0, sum = 0;
        for(int num : nums) {
            if(num % modulo == k) sum++;
            int t = sum % modulo;
            res += cnt[t - k] + cnt[t - k + modulo];
            cnt[t]++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}