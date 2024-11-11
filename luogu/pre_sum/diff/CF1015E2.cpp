/**
 * @Time : 2024/4/17-9:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 前缀和分解预处理出某个点 上下左右四个方向最多多少个连续的*
 * 这四个值中最小的一个就确定了星星的大小
 * 如果可以画一个星星，就要将相应的点都标记上 行和列分别标记
 * 这是一个区间操作 用+1表示涂了一次星星（因为允许重叠）
 * 因此可以用差分的思路来记录区间的操作 行列分开计算就可以一维差分解决问题
 *
 * cf1015e1 只是数据弱化版
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1005;
int n, m, lf[N][N], rgt[N][N], up[N][N], down[N][N], r_diff[N][N], c_diff[N][N];
string grid[N];

void init_row(int arr[N][N], int sign) {
    for(int i = 1; i <= n; i++) {
        for(int j = sign == 1 ? 1 : m, pre = j - sign; j >= 1 && j <= m; j += sign) {
            if(grid[i][j] != '*') pre = j;
            arr[i][j] = abs(j - pre) - 1;
        }
    }
}

void init_col(int arr[N][N], int sign) {
    for(int i = 1; i <= m; i++) {
        for(int j = sign == 1 ? 1 : n, pre = j - sign; j >= 1 && j <= n; j += sign) {
            if(grid[j][i] != '*') pre = j;
            arr[j][i] = abs(j - pre) - 1;
        }
    }
}

bool check() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] != '.') return false;
        }
    }
    return true;
}

void solve() {
    init_row(lf, 1), init_row(rgt, -1);
    init_col(up, 1), init_col(down, -1);
    vector<vector<int>> ans;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] == '.') continue;
            int dis = min({lf[i][j], rgt[i][j], up[i][j], down[i][j]});
            if(dis <= 0) continue;
            r_diff[i][j - dis]++, r_diff[i][j + dis + 1]--;
            c_diff[j][i - dis]++, c_diff[j][i + dis + 1]--;
            ans.push_back({i, j, dis});
        }
    }
    // 判断行涂的星星
    for(int i = 1; i <= n; i++) {
        for(int sum = 0, j = 1; j <= m; j++) {
            sum += r_diff[i][j];
            if(sum > 0) grid[i][j] = '.';
        }
    }
    // 判断列涂的星星
    for(int i = 1; i <= m; i++) {
        for(int sum = 0, j = 1; j <= n; j++) {
            sum += c_diff[i][j];
            if(sum > 0) grid[j][i] = '.';
        }
    }
    if(!check()) {
        cout << -1;
        return;
    }
    cout << ans.size() << "\n";
    for(auto& info : ans)
        cout << info[0] << " " << info[1] << " " << info[2] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> grid[i];
        grid[i] = '.' + grid[i];
    }
    solve();
};