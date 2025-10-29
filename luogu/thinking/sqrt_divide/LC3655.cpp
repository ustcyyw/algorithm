/**
 * @Time : 2025/10/28-13:06
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3655 2453 根号分治 差分算法（乘法版本）
 */
 /*
  * 发现当k很大的时候，单点修改也不会修改几个点，可以直接暴力，时间复杂度o(n / k)
  *
  * 当k比较小的时候，比如 k < m
  * 修改的一系列数字，可以根据k及其余数分类 转换成区间上的修改 这样修改操作就是o(1)的
  * 这里区间修改 类似于加法的差分，在mod意义下可以使用乘法的差分
  * 每个数要知道最终值的时候，分别去k属于[1,m]对应的组别里去查询多次操作累积的变化
  * 对每个数查询的时间复杂度是o(m)
  *
  * 两种不同类型的维护值的方式 每种方式下暴力求解时间复杂度都不高 使用根号分治
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}
// 预处理逆元
ll invF[N];
int init = []() -> int {
    for (int i = 1; i < N; i++)
        invF[i] = qPow(i, mod - 2);
    return 0;
}();

class Solution {
public:
    int n, m;
    vector<vector<vector<ll>>> arr;
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        n = nums.size(), m = sqrt(n);
        arr.assign(m, {});
        for(auto& query : queries) {
            int l = query[0], r = query[1], k = query[2], v = query[3];
            if(k >= m) {
                for(int i = l; i <= r; i += k)
                    nums[i] = (ll)nums[i] * v % mod;
            } else mul(l, r, k, v);
        }
        for(int k = 1; k < m; k++) {
            if(arr[k].empty()) continue;
            for(int id = 0; id < k; id++) {
                if(arr[k][id].empty()) continue;
                for(int i = 1; i < arr[k][id].size(); i++)
                    arr[k][id][i] = arr[k][id][i] * arr[k][id][i - 1] % mod;
            }
        }
        ll ans = 0;
        for(int i = 0; i < n; i++)
            ans ^= cal(nums[i], i);
        return ans;
    }

    ll cal(int num, int idx) {
        for(int k = 1; k < m; k++) {
            if(arr[k].empty()) continue;
            int id = idx % k;
            if(arr[k][id].empty()) continue;
            int j = (idx - id) / k;
            num = num * arr[k][id][j] % mod;
        }
        return num;
    }

    void mul(int l, int r, int k, int v) {
        if(arr[k].empty()) arr[k].assign(k, {});
        int id = l % k;
        if(arr[k][id].empty()) arr[k][id].assign(n / k + 3, 1);
        int lo = l / k, hi = (r - id) / k;
        arr[k][id][lo] = arr[k][id][lo] * v % mod;
        arr[k][id][hi + 1] = arr[k][id][hi + 1] * invF[v] % mod;
    }
};