/**
 * @Time : 2024/5/25-1:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1826D 前后缀分解
 */
 /*
  * 枚举中间的数
  * 左边 bi + l, 右边bk - r
  * 前缀找bi + i的最大值，后缀找bk - k的最大值
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, nums[N], pre[N];

void solve() {
    ll ans = 0;
    for(ll i = n, cur, p = INT_MIN; i >= 2; i--) {
        cur = nums[i] - i;
        ans = max(ans, p + nums[i] + pre[i - 1]);
        p = max(p, cur);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            pre[i] = max(pre[i - 1], nums[i] + i);
        }
        solve();
    }
};