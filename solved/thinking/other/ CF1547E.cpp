/**
 * @Time : 2024/7/12-12:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1547E 前后缀分解
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, pos[N], t[N], nums[N], ans[N];

void solve() {
    for(int i = n; i >= 1; i--) {
        ans[i] = min(nums[i], ans[i + 1] + 1);
    }
    for(int i = 1, pre = 2e9; i <= n; i++) {
        pre = min(pre + 1, nums[i]);
        cout << min(pre, ans[i]) << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        fill(nums, nums + n + 2, 2e9), fill(ans, ans + n + 2, 2e9);
        for(int i = 1; i <= k; i++)
            cin >> pos[i];
        for(int i = 1; i <= k; i++)
            cin >> t[i];
        for(int i = 1; i <= k; i++)
            nums[pos[i]] = t[i];
        solve();
    }
};