/**
 * @Time : 2022/5/8-9:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

/**
 * 子序列，并且只需要关注元素的相对大小
 * 在选定某个元素为最小值后，其它位置比它大的元素都可以放进该子序列
 * 也就是说和元素位置无关，只和大小有关，因此可以排序
 *
 * 如果选定位置i的元素为子序列的最小值，那么其右边[i+1, n)的所有元素都可以放入以它为最小值的子序列
 * [i+1, n)上的每一个元素都可选/不选，因此是2^k个子序列
 * 对总和的贡献为 -nums[i] * 2^k, k = n - i - 1
 *
 * 同理，选定nums[i]的元素为子序列的最大值，其左边的...
 */
class Solution {
public:
    int mod = 1000000007;
    int sumSubseqWidths(vector<int> &nums) {
        int n = nums.size();
        vector<long long> p(n + 1);
        p[0] = 1;
        for (int i = 1; i <= n; i++)
            p[i] = (p[i - 1] << 1) % mod;
        sort(nums.begin(), nums.end());
        long long res = 0;
        for (int i = 0; i < n; i++)
            res = (res + nums[i] * (p[i] - p[n - i - 1])) % mod;
        res = (res + mod) % mod;
        return (int) res;
    }
};

int main() {
    Solution s;
    vector<int> arr = {2, 1, 3};
    s.sumSubseqWidths(arr);
}