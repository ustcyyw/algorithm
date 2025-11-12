/**
 * @Time : 2024/7/3-10:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1399F 动态规划 可以用线段树优化
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, cache[3005];
vector<vector<int>> arr, inter;

int dfs(int idx) {
    // 某个区间内只含一个区间或者已经没有别的区间了 所能取的最大值就是它本身加上所包含的那个区间（或者没有包含区间）
    if(cache[idx] != -1) return cache[idx];
    int m = arr[idx].size();
    if(m <= 1) return cache[idx] = m + 1;
    if(m == dfs(arr[idx][0])) return cache[idx] = m + 1; // 层层嵌套的特殊情况
    // dp[i]: 长度为
    vector<int> dp(m, 0);
    int ans = 0;
    for(int i = 0; i < m; i++) {
        int I = arr[idx][i], cnt = dfs(I);
        dp[i] = cnt;
        for(int j = i - 1; j >= 0; j--) { // 这一步线性枚举可以使用线段树优化 但是要按右端点进行排序
            int J = arr[idx][j];
            if(inter[J][1] < inter[I][0])
                dp[i] = max(dp[i], dp[j] + cnt);
        }
        ans = max(ans, dp[i]);
    }
    return cache[idx] = ans + 1;
}

void solve() {
    sort(inter.begin(), inter.end());
    // 预处理一个区间能包含的其它所有区间
    for(int i = 0; i <= n; i++) {
        for(int j = 0, lo = inter[i][0], hi = inter[i][1]; j <= n; j++) {
            if(i == j) continue;
            if(lo <= inter[j][0] && inter[j][1] <= hi) arr[i].push_back(j);
        }
    }
    cout << dfs(0) - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        arr.assign(n + 1, {}), inter = {{-1, N}};
        fill(cache, cache + n + 5, -1);
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            inter.push_back({l, r});
        }
        solve();
    }
};