/**
 * @Time : 2024/4/26-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1102F
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
int n, m, ans = 0, full, grid[17][N], diff[17][17]; // diff[i][j]相邻的两行产生的最小差值

void init() {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int val = INT_MAX;
            for(int k = 0; k < m; k++)
                val = min(val, abs(grid[i][k] - grid[j][k]));
            diff[i][j] = diff[j][i] = val;
        }
    }
}
// 首尾产生的差值
int up_down_diff(int i, int j) {
    int res = INT_MAX;
    for(int k = 0; k < m - 1; k++)
        res = min(res, abs(grid[j][k] - grid[i][k + 1]));
    return res;
}

int cal(int up, int down) {
    int u = full ^ (1 << up) ^ (1 << down);
    vector<vector<int>> dp(u + 1, vector(n, - 1));
    function<int(int, int)> dfs = [&](int s, int i) -> int {
        if(s == 0) return diff[i][down];
        if(dp[s][i] != -1) return dp[s][i];
        int res = 0;
        for(int j = 0; j < n; j++) {
            int t = 1 << j;
            // j行已经被安排过了 或者i和j的差比最终答案还小 就没必要继续计算了
            if((s & t) == 0 || ans >= diff[i][j]) continue;
            res = max(res, min(diff[i][j], dfs(s ^ t, j)));
        }
        return dp[s][i] = res;
    };
    int res = 0;
    for(int i = 0; i < n; i++) {
        if(i != up && i != down)
            res = max(res, min(dfs(u ^ (1 << i), i), diff[up][i]));
    }
    return res;
}

void solve() {
    if(n == 1) ans = up_down_diff(0, 0);
    else if(n == 2)
        ans = min(diff[0][1], max(up_down_diff(0, 1), up_down_diff(1, 0)));
    else {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                int udd = up_down_diff(i, j);
                if(udd <= ans) continue;
                ans = max(ans, min(udd, cal(i, j)));
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    full = (1 << n) - 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
    }
    init();
    solve();
};