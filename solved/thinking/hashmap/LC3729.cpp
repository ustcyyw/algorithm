/**
 * @Time : 2025/10/27-14:25
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3729 2287 哈希表计数 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    /*
     * 如果只是求和为k的倍数的子数组 不管重复性 直接前缀和余数计数即可
     * 那么可以先算总的子数组数目 再减去重复的
     * 计算重复的子数组，可以利用数组非递减的性质，发现只有连续相同的数字才可能会出现重复子数组
     * 去重：先看最少多少个数字num可以凑成k的倍数
     */
    long long numGoodSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> map;
        map[0] = 1;
        ll ans = 0, sum = 0;
        for(int num : nums) {
            sum += num;
            int m = sum % k;
            ans += map[m], map[m]++;
        }
        for(int i = 0, j, n = nums.size(); i < n; i = j) {
            j = i + 1;
            while(j < n && nums[j] == nums[i]) j++;
            ans -= cal(k, j - i, nums[i]);
        }
        return ans;
    }

    ll cal(ll k, int len, ll num) {
        ll temp = lcm(num, k), base = temp / num;
        if(base == 0) return 0;
        ll mc = len / base * base;
        ll a = len - base + 1, b = len - mc + 1, cnt = mc / base;
        return (a + b) * cnt / 2 - cnt;
    }
};