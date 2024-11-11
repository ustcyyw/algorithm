/**
 * @Time : 2024/3/21-8:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 如果从图的连通性考虑
 * 优先将度数为1的点变为x 这样不会导致连通性被破坏
 * 但是如果所有点的度数都 > 1这个时候应该优先选什么点变为x 不好讨论
 *
 * 正向难做 反向处理 先把所有的.预设为x
 * 然后从其中一个x开始进行搜索 直到找到了n - k个x，再将他们都变为.
 * 这样就得到了有x个点，且连通性保持不变的结果了
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 505;
int T, n, m, k, dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
string grid[N];

void solve() {
    int si = -1, sj = -1, cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.') {
                grid[i][j] = 'X', cnt++;
                si = i, sj = j;
            }
        }
    }
    k = cnt - k; // 要将cnt - k个预先设置为X的再恢复.
    function<void(int, int)> dfs = [&](int i, int j) -> void {
        if(k == 0) return;
        grid[i][j] = '.', k--;
        for(int t = 0; t < 4; t++) {
            int x = i + dx[t], y = j + dy[t];
            if(x >= 0 && y >= 0 && x < n && y < m && grid[x][y] == 'X')
                dfs(x, y);
        }
    };
    if(si != -1) dfs(si, sj);
    for(int i = 0; i < n; i++)
        cout << grid[i] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        cin >> grid[i];
    solve();
};