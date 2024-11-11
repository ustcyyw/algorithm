/**
 * @Time : 2024/3/12-10:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 注意 本题中虽然 n*k = 1e9
 * 但是因为b[i] <= 1000，操作1变为任意一个b[i]实际上只需要最多十几次操作，记最大操作数为step
 * 在 k >= n * step的时候 可以全部拿走 直接输出
 * 否则进行0-1背包dp 时间复杂度上限20*n*n
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 1e3 + 5;
int T, n, k, step = 1, b[N], c[N], ope[N] = {0};

int init = []() -> int {
    deque<int> dq;
    dq.push_back(1);
    while(!dq.empty()) {
        int sz = dq.size();
        for(int i = 0; i < sz; i++) {
            int num = dq.front();
            for(int j = 1; j <= num; j++) {
                int nx = num + num / j;
                if(nx <= 1000 && ope[nx] == 0) ope[nx] = step, dq.push_back(nx);
            }
            dq.pop_front();
        }
        step++;
    }
    return 0;
}();

void solve() {
    if(n * step <= k) {
        cout << accumulate(c + 1, c + 1 + n, 0) << "\n";
        return;
    }
    vector<vector<int>> dp(n + 1, vector(k + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= k; j++) {
            dp[i][j] = max(dp[i - 1][j], j >= 1 ? dp[i][j - 1] : 0);
            if(j - ope[b[i]] >= 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - ope[b[i]]] + c[i]);
        }
    }
    cout << dp[n][k] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++)
            cin >> b[i];
        for (int i = 1; i <= n; i++)
            cin >> c[i];
        solve();
    }
};