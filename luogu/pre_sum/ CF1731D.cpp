/**
 * @Time : 2024/6/4-4:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1731D 二分 + 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 305, MV = 1e9;
typedef long long ll;
int T, n, m;
vector<vector<int>> grid, sum;

bool check(int l) {
    for(int i = 1; i <= n; i++) {
        for(int ls = 0, j = 1; j <= m; j++) {
            ls += grid[i][j] >= l;
            sum[i][j] = ls + sum[i - 1][j];
        }
    }
    for(int i = 1; i + l - 1 <= n; i++) {
        for(int j = 1; j + l - 1 <= m; j++) {
            int x2 = i + l - 1, y2 = j + l - 1;
            int cnt = sum[x2][y2] + sum[i - 1][j - 1] - sum[x2][j - 1] - sum[i - 1][y2];
            if(cnt == l * l) return true;
        }
    }
    return false;
}

void solve() {
    int lo = 1, hi = min(n, m);
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        grid = vector(n + 1, vector(m + 1, 0));
        sum = vector(n + 1, vector(m + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++)
                cin >> grid[i][j];
        }
        solve();
    }
};