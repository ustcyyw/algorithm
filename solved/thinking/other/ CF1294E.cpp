/**
 * @Time : 2024/6/19-10:58 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1294E 枚举
 */
/*
 * 每列是独立计算的 可以枚举每列要列轮换多少次
 * 预处理没一列的元素在原始状态下要轮转多少次才能到达正确的位置 并且进行统计
 * 枚举轮转次数i，如果到达正确位置轮转次数不是i就需要一次改变
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, m;
vector<vector<int>> grid;

int cal_row(int base) {
    vector<int> cnt(n, 0);
    for(int i = 0; i < n; i++) {
        int num = grid[i][base - 1] - base;
        // 对m取mod不为0的数 或者超过该列最大值的数 没办法通过轮转得到 不必统计
        if(num % m == 0 && num + base <= base + (n - 1) * m) {
            int t = num / m;
            if(i >= t) cnt[i - t]++;
            else cnt[i + n - t]++;
        }
    }
    int ans = n;
    for(int i = 0; i < n; i++) {
        int t = i + n - cnt[i];
        ans = min(ans, t);
    }
    return ans;
}

void solve() {
    int ans = 0;
    for(int i = 1; i <= m; i++) {
        ans += cal_row(i);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    grid = vector(n, vector(m, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
    }
    solve();
};