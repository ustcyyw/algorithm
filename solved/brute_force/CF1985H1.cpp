/**
 * @Time : 2025/1/14-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1985H1 1700 dfs 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5, mod = 998244353;
int T, n, m, id, cnt[N], row[N], col[N];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
vector<vector<bool>> marked;
vector<vector<int>> ids;
string grid[N];

void dfs(int x, int y) {
    marked[x][y] = true, ids[x][y] = id, cnt[id]++;
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx == 0 || ny == 0 || nx > n || ny > m) continue;
        if(marked[nx][ny] || grid[nx][ny] != '#') continue;
        dfs(nx, ny);
    }
}

void add(set<int>& set, int& sum, int x, int y) {
    if(grid[x][y] == '.') return;
    int i = ids[x][y];
    if(set.count(i)) return;
    set.insert(i), sum += cnt[i];
}

void init_row(int i) {
    set<int> set;
    int sum = 0;
    for(int j = 1; j <= m; j++) {
        if(grid[i][j] == '.') sum++;
        add(set, sum, i, j);
        if(i - 1 >= 1) add(set, sum, i - 1, j);
        if(i + 1 <= n) add(set, sum, i + 1, j);
    }
    row[i] = sum;
}

void init_col(int j) {
    set<int> set;
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(grid[i][j] == '.') sum++;
        add(set, sum, i, j);
        if(j - 1 >= 1) add(set, sum, i, j - 1);
        if(j + 1 <= m) add(set, sum, i, j + 1);
    }
    col[j] = sum;
}

void solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(marked[i][j] || grid[i][j] == '.') continue;
            id++;
            cnt[id] = 0, dfs(i, j);
        }
    }
    int ans = 0;
    // 处理添加行
    for(int i = 1; i <= n; i++) {
        init_row(i);
        ans = max(ans, row[i]);
    }
    // 处理添加列
    for(int i = 1; i <= m; i++) {
        init_col(i);
        ans = max(ans, col[i]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        id = 0;
        marked = vector(n + 2, vector(m + 2, false));
        ids = vector(n + 2, vector(m + 2, -1));
        for(int i = 1; i <= n; i++) {
            cin >> grid[i];
            grid[i] = '.' + grid[i];
        }
        solve();
    }
};