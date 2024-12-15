/**
 * @Time : 2024/12/14-11:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1722F 1700 模拟 dfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, dx[8] = {1,-1,0,0,1,-1,1,-1}, dy[8] = {0,0,1,-1,1,-1,-1,1};
string grid[52];

int dfs(int x, int y, int& x1, int& x2, int& y1, int& y2) {
    grid[x][y] = '.';
    x1 = min(x, x1), x2 = max(x, x2);
    y1 = min(y, y1), y2 = max(y, y2);
    int cnt = 1;
    for(int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx < 0 || ny < 0 || nx == n || ny == m || grid[nx][ny] != '*') continue;
        cnt += dfs(nx, ny, x1, x2, y1, y2);
    }
    return cnt;
}

bool check() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.') continue;
            int x1 = i, x2 = i, y1 = j, y2 = j;
            int cnt = dfs(i, j, x1, x2, y1, y2);
            if(cnt != 3 || x2 - x1 > 1 || y2 - y1 > 1) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        cout << (check() ? "YES" : "NO") << "\n";
    }
};