/**
 * @Time : 2024/6/27-5:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1360G 构造算法 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 52;
typedef long long ll;
int T, n, m, a, b;
vector<vector<int>> grid;

bool check() {
    for(int i = 0; i < m; i++) {
        int cnt = 0;
        for(int j = 0; j < n; j++)
            cnt += grid[j][i];
        if(cnt != b) return false;
    }
    return true;
}

void solve() {
    for(int i = 0, j = 0; i < n; i++) {
        for(int k = 0; k < a; k++, j = (j + 1) % m)
            grid[i][j] = 1;
    }
    if(!check()) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cout << grid[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> a >> b;
        grid.assign(n, vector(m, 0));
        solve();
    }
};