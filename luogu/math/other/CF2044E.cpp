/**
 * @Time : 2024/12/16-10:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2044E 数学 暴力枚举
 */
 /*
  * k ^ n，n是非负整数
枚举n
y = x * k ^ n   x太小 达不到y的左边界；x太大 超过y的右边界
n = 0, y = x
n = 1, y = x * k

x1 * a >= loy,   x1 >= loy / a, 向上取整
x2 * a <= hiy,   x2 <= hiy / a, 向下取整
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, k, l1, r1, l2, r2;

void solve() {
    ll ans = 0, temp = 1;
    while(temp <= (ll)1e9) {
        ll lo = l2 % temp == 0 ? l2 / temp : l2 / temp + 1, hi = r2 / temp;
        lo = max(lo, l1), hi = min(hi, r1);
        if(lo <= hi) ans += hi - lo + 1;
        temp *= k;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> k >> l1 >> r1 >> l2 >> r2;
        solve();
    }
};