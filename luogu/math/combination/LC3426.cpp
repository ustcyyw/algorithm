/**
 * @Time : 2025/1/19-4:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3426 数学 排列组合
 */
 /*
  * 枚举第一个棋子放置的位置x 考虑这个位置和其它棋子的距离总和
  * 剩下还能在 total-1 个位置放k-1个棋子
  * 剩下的 total-1 个位置 它们是平等的 被放上棋子的概率均等（有棋子存在的放置方案数相同）
  * 这 total-1 个位置中 再固定其中一个位置y再放一个棋子
  * 现在已经有x和y两个位置有棋子 放了两个棋子 所有可能的放置方法就是 C(total - 2, k - 2)
  * 所以确定x的情况下，y给x贡献的距离和为 dis(x,y) * C(total - 2, k - 2)
  * 所有位置都可以给x贡献距离和 sum{dis(x,yi)} * C(total - 2, k - 2)
  * 然后就是求x以外的点与x的距离和 将行坐标和列坐标独立求和
  * 在求列坐标的贡献时，每一行的坐标恭喜都相同 算出来后乘行数即可
  * 具体每一列的贡献 就是左右两个等差数列和
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
    int distanceSum(int m, int n, int k) {
        int total = m * n;
        ll base = C(total - 2, k - 2) % mod, s = 0;
        for(ll i = 0; i < m; i++) {
            ll s1 = (i * (i + 1) / 2 + (m - 1 - i) * (m - i) / 2) * n;
            for(ll j = 0; j < n; j++) {
                ll s2 = (j * (j + 1) / 2 + (n - 1 - j) * (n - j) / 2) * m;
                s = (s + s1 + s2) % mod;
            }
        }
        return base * s % mod * invF[2] % mod;
    }
};