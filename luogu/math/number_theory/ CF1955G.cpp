/**
 * @Time : 2024/4/11-3:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 1e6以下的数 最多有240个因子。要求最大gcd 一定经过起点和终点
  * 最终答案一定是起点和终点公共因子
  * 枚举这可能的240个因子 num，在行走的每一步也都要求路过的数字是 num的倍数
  * 方格大小100 * 100 每个格子都访问也才1e4 看是否从起点可以走到终点
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 105;
int T, n, m, grid[N][N], dp[N][N];

unordered_set<int> get_factors(int num) {
    unordered_set<int> set;
    for(int i = 1; i * i <= num; i++) {
        if(num % i == 0)
            set.insert(i), set.insert(num / i);
    }
    return set;
}

bool check(int num) {
    dp[1][1] = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(i == 1 && j == 1) continue;
            dp[i][j] = grid[i][j] % num == 0 && (dp[i - 1][j] || dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

void solve() {
    unordered_set<int> s = get_factors(grid[1][1]), t = get_factors(grid[n][m]);
    int res = 1;
    for(int f : s) {
        if(!t.count(f)) continue;
        if(check(f)) res = max(f, res);
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++)
                cin >> grid[i][j];
        }
        solve();
    }
};