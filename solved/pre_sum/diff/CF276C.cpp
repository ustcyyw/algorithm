/**
 * @Time : 2024/12/31-8:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF276C 1500 差分 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, nums[N], diff[N];

void solve() {
    sort(nums, nums + n + 1);
    for(int i = 1; i <= n; i++)
        diff[i] += diff[i - 1];
    sort(diff, diff + n + 1);
    ll ans = 0;
    for(int i = 1; i <= n; i++)
        ans += (ll)diff[i] * nums[i];
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> q;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            diff[l]++, diff[r + 1]--;
        }
        solve();
    }
};