/**
 * @Time : 2025/2/25-9:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : F803A 1400 构造 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 5, M = 400;
int n, k, grid[105][105];

void solve() {
    for(int i = 0; i < n && k; i++) {
        if(grid[i][i] == 0) {
            grid[i][i] = 1, k--;
            if(k > 0 && k % 2 == 1) grid[i + 1][i + 1] = 1, k--;
        }
        for(int j = i + 1; j < n && k; j++) {
            grid[i][j] = grid[j][i] = 1;
            k -= 2;
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    if(n * n < k) {
        cout << -1;
        return 0;
    }
    solve();
}