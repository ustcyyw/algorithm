/**
 * @Time : 2025/2/13-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF616C 1600 dfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5, mod = 998244353;
int T, n, m, dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0}, sz[N * N], ids[N][N];
string grid[N];

void dfs(int x, int y, int id) {
    ids[x][y] = id, sz[id]++, grid[x][y] = 'A';
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx == n || ny == m || grid[nx][ny] != '.') continue;
        dfs(nx, ny, id);
    }
}

int cal(int x, int y) {
    int ans = 1;
    set<int> st;
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx == n || ny == m || grid[nx][ny] == '*') continue;
        int id = ids[nx][ny];
        if(!st.count(id))
            st.insert(id), ans += sz[id];
    }
    return ans;
}

void solve() {
    vector<string> ans(n, string(m, '.'));
    for(int i = 0, id = 1; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.')
                dfs(i, j, id++);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '*') {
                int cnt = cal(i, j) % 10;
                ans[i][j] = (char)('0' + cnt);
            }
        }
    }
    for(int i = 0; i < n; i++)
        cout << ans[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        solve();
    }
};