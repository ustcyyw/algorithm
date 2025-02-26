/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
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