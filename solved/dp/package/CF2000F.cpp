/**
 * @Time : 2024/11/22-4:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2000F 动态规划 背包 1900
 */

#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e3 + 5;
int T, n, k, a[N], b[N];

vector<int> get_cost(int x, int y) {
    vector<int> ans(x + y + 1, x * y + 5);
    ans[0] = 0;
    for(int i = 0; i <= x; i++) {
        for(int j = 0; j <= y; j++) {
            ans[i + j] = min(ans[i + j], i * y + j * x - i * j);
        }
    }
    return ans;
}

void solve() {
    vector<vector<int>> dp(n + 1, vector(k + 1, (int)1e9));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        vector<int> cost = get_cost(a[i], b[i]);
        for(int j = 0; j <= k; j++) {
            for(int p = 0; p < cost.size() && p <= j; p++)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - p] + cost[p]);
        }
    }
    cout << (dp[n][k] == (int)1e9 ? -1 : dp[n][k]) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i] >> b[i];
        solve();
    }
};