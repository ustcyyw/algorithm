/**
 * @Time : 2024/6/4-3:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1371D 贪心
 */
 /*
  * 行列是独立的
  * 从一个维度来看 要平均分配
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 305, MV = 1e9;
typedef long long ll;
int T, n, k;
vector<vector<int>> grid;

void solve() {
    int base = k / n, mod = k % n;
    for(int i = 0, j = 0; i < n; i++) {
        int add = mod > 0 ? 1 : 0;
        for(int t = 0; t < base + add; t++, j = (j + 1) % n)
            grid[i][j] = 1;
        if(mod > 0) mod--;
    }
    cout << (k % n != 0 ? 2 : 0) << "\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << grid[i][j];
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        grid = vector(n, vector(n, 0));
        solve();
    }
};