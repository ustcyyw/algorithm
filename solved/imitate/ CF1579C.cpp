/**
 * @Time : 2024/7/13-9:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 模拟
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k;
vector<vector<bool>> marked;
string grid[12];

int maxLen(int x, int y) {
    int i = 1;
    while (x - i >= 0 && y - i >= 0 && y + i <= m - 1 &&
           grid[x - i][y - i] == '*' && grid[x - i][y + i] == '*')
        i++;
    return i - 1;
}

void fill(int x, int y) {
    for (int i = 0; ; i++) {
        if (x - i >= 0 && y - i >= 0 && y + i <= m - 1 &&
            grid[x - i][y - i] == '*' && grid[x - i][y + i] == '*')
            marked[x - i][y - i] = marked[x - i][y + i] = true;
        else break;
    }
}

bool solve() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '*' && maxLen(i, j) >= k)
                fill(i, j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(grid[i][j] == '*' && !marked[i][j])
                return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> k;
        marked.assign(n, vector(m, false));
        for (int i = 0; i < n; i++) {
            cin >> grid[i];
        }
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};