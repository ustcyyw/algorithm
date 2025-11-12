/**
 * @Time : 2025/1/23-8:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF12F 2100 构造算法
 */
 /*
  * 第一行是随便顺序填的
  * 然后手玩发现 第i行0右边的位置 [i+1, n] 都是上一行[i+1,n]上的数左移动一个位置得到（视为循环数组）
  * 这样得到的第i行 会有缺的数 也会用重复的数 将重复的数用缺失的数替换即可
  * 而0左边的位置 则是通过对称直接填写即可。
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e3 + 5, mod = 998244353;
int T, n, grid[N][N];

void fill_line(int i) {
    vector<int> idx, miss(n, 1), cnt(n, 0);
    for(int j = 1; j <= n; j++) {
        int num = grid[i][j];
        miss[num] = 0, cnt[num]++;
        if(cnt[num] > 1) idx.push_back(j);
    }
    for(int num = 0; num < n && !idx.empty(); num++) {
        if(miss[num]) {
            grid[i][idx.back()] = grid[idx.back()][i] = num;
            idx.pop_back();
        }
    }
}

void solve() {
    for(int i = 1; i <= n; i++)
        grid[1][i] = grid[i][1] = i - 1; // 特殊填第一行
    for(int i = 2; i < n; i++) {
        for(int j = i + 1; j < n; j++)
            grid[i][j] = grid[j][i] = grid[i - 1][j + 1];
        grid[i][n] = grid[n][i] = grid[i - 1][i + 1];
        fill_line(i);
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++)
            cout << grid[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        solve();
    }
};