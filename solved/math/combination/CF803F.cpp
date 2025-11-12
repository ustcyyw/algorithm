/**
 * @Time : 2025/2/25-10:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF803F 2000 数学 调和级数 组合数学
 */
/*
  * 令 f(x): gcd为x的倍数的子序列数目; g(x): gcd = x的子序列数目
  * 要求的答案就是 g(1) = f(1) - g(2) - g(3) ... g(v), v是最大值
  *
  * g(2) = f(2) - g(4) - g(6) - ... 上边界是g(v)
  * g(3) = f(3) - g(6) - g(9) - ... 上边界是g(v)
  * 所以计算g(x)所需的计算次数是 v / x
  * 计算所有g(x)所需的计算次数是 v * (1 + 1 / 2 + 1 / 3 + ... + 1 / v) = v * logv
  * （调和级数求和）
  *
  * 计算f(x): 找到x的倍数的所有数 这些数任选 他们的gcd都是x的倍数
  * 假设有cx个数 那么非空序列就有 2 ^ cx - 1 个
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 1e9 + 7;
int n, v, cnt[N];
ll p[N], g[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        cnt[num]++, v = max(v, num);
    }
    p[0] = 1;
    for(int i = 1; i <= n; i++)
        p[i] = p[i - 1] * 2 % mod;
    for(int i = v; i >= 1; i--) {
        int cx = 0;
        for(int j = i; j <= v; j += i) // 计算i的倍数 一共有多少个数
            cx += cnt[j];
        g[i] = p[cx] - 1; // 用g[i]暂时存f[i]的值
        for(int j = 2 * i; j <= v; j += i)
            g[i] -= g[j];
        g[i] = (g[i] % mod + mod) % mod;
    }
    cout << g[1] << "\n";
}