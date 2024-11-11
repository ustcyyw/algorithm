/**
 * @Time : 2024/3/13-1:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * n = 5000 想到可以枚举翻转区间
  * 但是注意到 翻转区间[lo, hi]和翻转区间[lo - 1, hi + 1]
  * 区间[lo - 1, hi + 1]上的和 = 区间[lo, hi]上的和 + 增加的两个边界元素贡献的和
  * 于是可以使用中心扩展（类似于找回文子字符串平方复杂度的方法）
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 5005;
ll T, n, a[N], b[N], sum[N] = {0};

void solve() {
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + a[i] * b[i];
    ll res = sum[n];
    function<void(int, int)> f = [&](int lo, int hi) -> void {
        ll temp = 0;
        while(lo >= 1 && hi <= n) {
            temp += a[lo] * b[hi] + (lo != hi ? a[hi] * b[lo] : 0);
            res = max(res, temp + sum[lo - 1] + sum[n] - sum[hi]);
            lo--, hi++;
        }
    };
    for(int i = 1; i < n; i++)
        f(i, i), f(i, i + 1);
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    solve();
};