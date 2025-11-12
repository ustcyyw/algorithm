/**
 * @Time : 2025/1/14-3:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1985H2 2200 dfs 枚举 差分
 */
/*
  * 像h1一样先预处理行与列填充满之后 以这一行/列为主的连通块有多少个格子 row[i]/col[j]
  * 但是h2要求行列都填充，那么会出现的问题是 有些连通块会同时连着选定的行和列
  * 可以考虑在选定某一列的时候 枚举行时 先求row[i] + col[j]
  * 这样同时连接了i行、j列的连通块的贡献就算了两次 要减去
  * 可以在预处理col[j]时，将连接上的连通块的上下范围[l,r]得出
  * 那么行号在[l-1,r+1]的行在计算时 都要减去这个连通块的值 可以使用差分数组来记录这个信息
  *
  * 另外注意 对于格子gird[i][j]的处理
  * 在预处理row[i], col[j]时，空格子分别会计算到该行/列的连通块中一次
  * 因此要在加和时-1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 5, mod = 998244353;
int T, n, m, id, up[N], down[N], cnt[N], row[N], col[N];
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
vector<vector<bool>> marked;
vector<vector<int>> ids;
string grid[N];

void dfs(int x, int y) {
    marked[x][y] = true, ids[x][y] = id, cnt[id]++;
    up[id] = min(x, up[id]), down[id] = max(x, down[id]);
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if(nx == 0 || ny == 0 || nx > n || ny > m) continue;
        if(marked[nx][ny] || grid[nx][ny] != '#') continue;
        dfs(nx, ny);
    }
}

void add_row(set<int>& set, int& sum, int x, int y) {
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
        add_row(set, sum, i, j);
        if(i - 1 >= 1) add_row(set, sum, i - 1, j);
        if(i + 1 <= n) add_row(set, sum, i + 1, j);
    }
    row[i] = sum;
}

void add_col(vector<int>& diff, set<int>& set, int& sum, int x, int y) {
    if(grid[x][y] == '.') return;
    int i = ids[x][y];
    if(set.count(i)) return;
    set.insert(i), sum += cnt[i];
    int u = up[i], d = down[i];
    diff[u - 1] -= cnt[i], diff[d + 2] += cnt[i];
}

void init_col(vector<int>& diff, int j) {
    set<int> set;
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(grid[i][j] == '.') sum++;
        add_col(diff, set, sum, i, j);
        if(j - 1 >= 1) add_col(diff, set, sum, i, j - 1);
        if(j + 1 <= m) add_col(diff, set, sum, i, j + 1);
    }
    col[j] = sum;
}

void solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(marked[i][j] || grid[i][j] == '.') continue;
            id++;
            cnt[id] = 0, up[id] = INT_MAX, down[id] = -1;
            dfs(i, j);
        }
    }
    // 处理添加行
    for(int i = 1; i <= n; i++)
        init_row(i);
    // 处理列 此时针对每一列再枚举行
    int ans = 0;
    for(int j = 1; j <= m; j++) {
        vector<int> diff(n + 5, 0);
        init_col(diff, j);
        for(int i = 1, sum = diff[0]; i <= n; i++) {
            sum += diff[i];
            int temp = col[j] + row[i] + sum;
            if(grid[i][j] == '.') temp--;
            ans = max(ans, temp);
        }
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