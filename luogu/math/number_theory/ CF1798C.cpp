/**
 * @Time : 2024/5/31-4:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1798C 数学 + 贪心
 */
/*
 * 在同一个标签下 假设价格为c
 * 那么所有的 bi * di = c
 * 1. 所有的bi都是c的因子，因此c为lcm(bi)的倍数
 * 2. di = c / bi, 并且有 ai % di = 0
 * ai % (c / bi) = 0, 也就是 ai * bi % c = 0
 * 那么c应该是所有ai * bi的最大公约数的因子
 * 所以 要能找到一个合法的c  gcd(ai * bi) % lcm(bi) = 0
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, a[N], b[N];

void solve() {
    int cnt = 0;
    for(ll i = 1, j, g, l; i <= n; ) {
        j = i + 1, g = a[i] * b[i], l = b[i], cnt++;
        while(j <= n) {
            g = gcd(g, a[j] * b[j]), l = lcm(l, b[j]);
            if(g % l != 0) break;
            j++;
        }
        i = j;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i] >> b[i];
        solve();
    }
};