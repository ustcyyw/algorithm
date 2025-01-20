/**
 * @Time : 2025/1/19-3:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3428 贡献法 数学 排列组合
 */
 /*
  * 排序后 枚举作为子序列最小元素的nums[i]
  * 并且注意到k <= 100 可以暴力枚举子序列的长度
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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

// 预处理阶乘 和 阶乘的逆元
ll x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

// 组合数 C(n,a) n个元素取a个
ll C(int n, int a) {
    if(n < a) return 0;
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

class Solution {
public:
    int minMaxSums(vector<int>& nums, int k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            ll num = nums[i], sum = 0;
            for(int m = 1, total = n - 1 - i; m <= min(k, total + 1); m++) {
                sum = (sum + C(total, m - 1)) % mod;
            }
            ans = (ans + num * sum % mod) % mod;
        }
        for(int i = n - 1; i >= 0; i--) {
            ll num = nums[i], sum = 0;
            for(int m = 1, total = i; m <= min(k, total + 1); m++) {
                sum = (sum + C(total, m - 1)) % mod;
            }
            ans = (ans + num * sum % mod) % mod;
        }
        return ans;
    }
};