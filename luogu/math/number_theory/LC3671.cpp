/**
 * @Time : 2025/10/21-23:15
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3671 2675 数学 数论 <套路>倍数容斥 动态规划 线段树优化dp
 */
 /*
  * 本题需要解决gcd为g且递增的子序列有多少个，并且g的值从1到数组最大值mv
  * g是[1,mv]上连续的，且涉及到gcd 想到倍数容斥的套路做法
  * 令g[i]为gcd为i的倍数的满足条件的子序列数量，f[i]为gcd值恰好为i的满足条件的子序列数量
  * 那么f[i] = g[i] - sum{f[2i] + f[3i] + ... f[k*i]}
  * 求g数组的时候，应该先将原本数组中的数num，按其因子i进行分组
  * 这样在i分组中的这些数构成的子序列gcm就是i的倍数，就可以拿来求g[i]了
  * 对于i分组arr[i], 要求的是递增子序列，线性动态规划
  * dp[i] = sum{dp[j]}, for arr[j] < arr[i], 显然可以使用线段树优化
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 7e4 + 5;
ll g[N], f[N];
#define ls x << 1
#define rs (x << 1) | 1

vector<int> divide[N];

int init = []() -> int {
    for(int i = 1; i < N; i++) {
        for(int j = i; j < N; j += i)
            divide[j].push_back(i);
    }
    return 0;
}();


class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = (val[x] + v) % mod;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = (val[ls] + val[rs]) % mod;
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = (res + search(rs, mid + 1, r, a, b)) % mod;
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

vector<int> scatter(vector<int>& num) {
    vector<int> pos = num;
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    return pos;
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(vector<int>& pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

class Solution {
public:
    int totalBeauty(vector<int>& nums) {
        int mv = *max_element(nums.begin(), nums.end());
        vector<vector<int>> aux(mv + 1);
        for(int num : nums) {
            for(int d : divide[num])
                aux[d].push_back(num);
        }
        for(int i = 1; i <= mv; i++)
            g[i] = cal(aux[i]);
        ll ans = 0;
        for(int i = mv; i >= 1; i--) {
            f[i] = g[i];
            for(int j = 2 * i; j <= mv; j += i)
                f[i] = (f[i] - f[j] + mod) % mod;
            ans = (ans + f[i] * i % mod) % mod;
        }
        return ans;
    }

    ll cal(vector<int>& nums) {
        vector<int> pos = scatter(nums);
        int n = nums.size(), m = pos.size();
        SegmentTree st(m);
        vector<ll> dp(n, 0ll);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int t = find(pos, nums[i]);
            dp[i] = ((t > 0 ? st.search(0, t - 1) : 0) + 1) % mod;
            ans = (ans + dp[i]) % mod;
            st.add(t, dp[i]);
        }
        return ans;
    }
};