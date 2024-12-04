/**
 * @Time : 2024/12/3-3:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1980E 1600 模拟 构造
 */
 /*
  * 列换操作 在同一行的元素还是在同一行
  * 换行操作 在同一行的元素还是在同一行
  * 所以必须是行与行元素完全相同 标识出每行的最小元素 通过最小元素来对应行
  * 然后选其中一行为排序标准 将另外一个矩阵的对应行按此标准排序
  * 排序后只能保证这一行相等 还要检查其它行
  * 只要对应行是相同的 总能通过换行操作让两个矩阵完全一致
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m;
vector<vector<int>> a, b;

map<int, int> init(vector<vector<int>>& grid) {
    map<int, int> ans;
    for(int i = 1; i <= n; i++) {
        int val = INT_MAX;
        for(int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            val = min(val, grid[i][j]);
        }
        ans[val] = i;
    }
    return ans;
}

void exch(vector<vector<int>>& grid, int j1, int j2) {
    for(int i = 1; i <= n; i++)
        swap(grid[i][j1], grid[i][j2]);
}

bool solve() {
    map<int, int> map1 = init(a), map2 = init(b);
    map<int, int> col;
    int r1 = map1[1], r2 = map2[1];
    for(int i = 1; i <= m; i++)
        col[b[r2][i]] = i;
    for(int i = 1; i <= m; i++) {
        if(!col.count(a[r1][i])) return false;
        int num = a[r1][i], j = col[num];
        exch(b, i, j);
        col[b[r2][j]] = j;
    }
    for(auto& p : map1) {
        if(!map2.count(p.first)) return false;
        int num = p.first, i1 = p.second, i2 = map2[num];
        for(int j = 1; j <= m; j++)
            if(a[i1][j] != b[i2][j]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> m;
        a.assign(n + 1, vector(m + 1, 0)), b.assign(n + 1, vector(m + 1, 0));
        cout << (solve() ? "YES" : "NO") << "\n";
    };
};