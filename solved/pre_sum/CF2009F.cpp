/**
 * @Time : 2025/1/4-4:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2009F 1700 前缀和 分类讨论 模拟
 */
/*
  * 前缀和 主要是细心分类讨论
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, q, sum[N], base;

void cal(ll pos, int& x, int& k, int& x1) {
    k = pos % n == 0 ? pos / n : pos / n + 1;
    x1 = k == 1 ? 1 : n - (k - 2);
    x = pos % n == 0 ? n : pos % n;
}
// 计算位置x在原数组中的下标
int calIdx(int x, int x1) {
    if(x1 <= x) return x - x1 + 1;
    int xn = x1 - 1;
    return n - (xn - x);
}

ll solve(ll l, ll r) {
    int xl, xl1, kl, xr, xr1, kr;
    cal(l, xl, kl, xl1), cal(r, xr, kr, xr1);
    int idxL = calIdx(xl, xl1), idxR = calIdx(xr, xr1);
    if(kl == kr) {
        if(idxL <= idxR) return sum[idxR] - sum[idxL - 1];
        return base - sum[idxL - 1] + sum[idxR];
    }
    int lastL = kl == 1 ? n : kl - 1, lastR = kr == 1 ? n : kr - 1;
    ll vl = xl1 <= xl ? sum[lastL] - sum[idxL - 1] : base - (sum[idxL - 1] - sum[kl - 1]);
    ll vr = xr1 > xr ? sum[idxR] - sum[kr - 1] : base - (sum[lastR] - sum[idxR]);
    return vl + vr + base * (kr - kl - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> q;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum[i] = sum[i - 1] + num;
        }
        base = sum[n];
        for(ll i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << solve(l, r) << "\n";
        }
    }
};