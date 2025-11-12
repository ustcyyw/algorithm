/**
 * @Time : 2024/12/29-4:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3405 数学 组合数学
 */
 /*
  * 长度位n的数组 一共有n-1个下标可以满足相等条件
  * 有k个位置是相等的 那么就有n-k-1个位置不相等
  * 选n-k-1个位置不相等 然后安排这些位置的后一个数 只要不和前一个数相同即可 因此有m-1种选法
  * 由于不管怎么安排 都是看前一个数去安排后一个数 因此第一个数先从m个数种任选一个
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
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        return C(n - 1, n - k - 1) * m % mod * qPow(m - 1, n - k - 1) % mod;
    }
};
