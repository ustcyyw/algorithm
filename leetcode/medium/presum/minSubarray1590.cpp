/**
 * @Time : 2022/12/5-5:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 假设整个数组的和为total
     * 如果total % p == 0，不用移除就可以满足要求，直接返回0
     * 否则记 mod = total % p
     * 要移除的子数组的和为 sumT = mod + k0 * p，这样才能在移除后数组和被p整除
     *
     * 子数组的和，想到了前缀和
     * 假设sum[i] % p = m, 那么 sum[i] = m + k1 * p
     * sum[j] % p = n, 那么 sum[j] = n + k2 * p
     * j > i, 子数组[i + 1, j]的和为sum[j] - sum[i] = n - m + (k2 - k1)p
     * 如果这个子数组能的和为sumT,就找到了一个可能的答案
     * 此时满足 n - m + (k2 - k1)p = mod + k0 * p
     * n - m = mod + (k0 + k1 - k2) * p
     * 两边对p取模得 (n - m) % p = mod
     * 因此n和m满足关系
     * n >= m 时  n - m = mod
     * n < m 时 n - m为负数，要取模得一个正数，其实是拿n - m + p去取模，因此 n - m + p = mod
     *
     * 于是可得 m = n - mod 或者 = n - mod + p
     *
     * 因为是求最小子数组，只需要记录sum[i] % p出现的最近一次即可。
     * 然后查看是否存在前置得m，更新最小长度
     */
    int minSubarray(vector<int>& nums, int p) {
        unordered_map<int, int> map;
        long total = accumulate(nums.begin(), nums.end(), 0l);
        int n = nums.size(), res = n, mod = total % p;
        if(mod == 0) return 0;
        map[0] = -1;
        for(int i = 0, sum = 0; i < n; i++){
            sum += nums[i];
            sum %= p;
            if(map.count(sum - mod)) res = min(res, i - map[sum - mod]);
            if(map.count(sum - mod + p)) res = min(res, i - map[sum - mod + p]);
            map[sum] = i;
        }
        return res == n ? -1 : res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {8,32,31,18,34,20,21,13,1,27,23,22,11,15,30,4,2};
    s.minSubarray(arr, 148);
    cout << 0 << endl;
}