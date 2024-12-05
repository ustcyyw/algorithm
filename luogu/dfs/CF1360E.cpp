/**
 * @Time : 2024/12/4-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1360E 1300 搜索 dfs
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k;
string grid[55];

string check() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            if(grid[i][j] == '1') return "NO";
    }
    return "YES";
}

void dfs(int x, int y) {
    grid[x][y] = '2';
    if(x - 1 >= 0 && grid[x - 1][y] == '1') dfs(x - 1, y);
    if(y - 1 >= 0 && grid[x][y - 1] == '1') dfs(x, y - 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        for(int i = 0; i < n; i++) {
            if(grid[n - 1][i] == '1') dfs(n - 1, i);
            if(grid[i][n - 1] == '1') dfs(i, n - 1);
        }
        cout << check() << "\n";
    };
};