/**
 * @Time : 2024/11/22-5:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2000E 贪心 1400
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, k, q, height[N];

void solve() {
    vector<int> points;
    for(int i = 1; i <= n; i++) {
        int up = max(1, i - k + 1), down = min(n - k + 1, i);
        for(int j = 1; j <= m; j++) {
            int left = max(1, j - k + 1), right = min(m - k + 1, j);
            points.push_back((down - up + 1) * (right - left + 1));
        }
    }
    sort(points.begin(), points.end());
    ll ans = 0;
    for(int i = q, j = points.size() - 1; i >= 1; i--, j--)
        ans += (ll)height[i] * points[j];
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> m >> k >> q;
        for(int i = 1; i <= q; i++)
            cin >> height[i];
        sort(height + 1, height + q + 1);
        solve();
    }
};