/**
 * @Time : 2024/4/2-9:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1005;
int T, n, m, k, ids[N][N], dx[4] = {1,-1,0,0}, dy[4] = {0,0,1,-1};
vector<int> cnt;
vector<vector<bool>> marked;
string s[N];

int dfs(int id, int x, int y) {
    int ans = 0;
    marked[x][y] = true, ids[x][y] = id;
    for(int i = 0; i < 4; i++) {
        int nx = dx[i] + x, ny = dy[i] + y;
        if(nx < 0 || ny < 0 || nx >= n || ny >= m || marked[nx][ny]) continue;
        if(s[nx][ny] == '*') ans++;
        else ans += dfs(id, nx, ny);
    }
    return ans;
}

void init() {
    for(int i = 0, id = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(marked[i][j] || s[i][j] == '*') continue;
            cnt.push_back(dfs(id, i, j));
            id++;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    cnt.clear();
    marked = vector(n, vector(m, false));
    for(int i = 0; i < n; i++)
        cin >> s[i];
    init();
    for(int i = 0, x, y; i < k; i++) {
        cin >> x >> y;
        cout << cnt[ids[x - 1][y - 1]] << "\n";
    }
};