/**
 * @Time : 2025/4/28-10:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1009C 1700 贪心 数学
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353;
ll T, n, m;

ll cal(ll c) {
    return c * (c + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    ll half = n / 2, reduce = cal(half) + cal(n - 1 - half), add = cal(n - 1);
    ll sum = 0;
    for(int i = 1, x, d; i <= m; i++) {
        cin >> x >> d;
        sum += x * n;
        if(d < 0) sum += d * reduce;
        else sum += add * d;
    }
    printf("%.10Lf\n", (long double)sum * 1.0 / n);
}