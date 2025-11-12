/**
 * @Time : 2024/5/29-10:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1898C
 */
/*
 * 从左上角走到右下角 一定要走至少need = n + m - 2
 * 可以走最上面和最右边路线 颜色交替变化
 * 除开need，还要走k - need步
 * 可以发现在格子里面走 走一个正方形可以走4步
 * 走一个长为2宽为1的长方形 可以走6步
 * 并且都会回到原点
 * 这两个圈的涂色法 可以画图看 因为最右边的颜色已经涂好了
 * 通过4和6的重复使用 可以构造出所有除（0，2）以外的偶数
 * 因此如果k - need为偶数，可以先从左上角走到右下角，然后绕圈
 * 特殊处理k - need = 2的情况 这种情况没法绕圈
 * 但是如果k - need为奇数，那么就没法办法设计路线 也是可以画图看
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k, row[17][17], col[17][17];

void solve() {
    int need = n + m - 2;
    if(need > k || (k - need) % 2 == 1) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    if(k - need == 2) { // 特殊处理还剩2的情况 这种情况不能靠走4和6的圈来完成 可以先绕一个路
        row[1][0] = 2;
        col[0][0] = col[0][1] = 1;
    }
    int color = 1;
    for(int i = 0; i < m - 1; i++) {
        row[0][i] = color;
        color = color == 1 ? 2 : 1;
    }
    for(int i = 0; i < n - 1; i++) {
        col[i][m - 1] = color;
        color = color == 1 ? 2 : 1;
    }
    int c = col[n - 2][m - 1], oc = c == 1 ? 2 : 1;
    col[n - 2][m - 2] = c, col[n - 2][m - 3] = oc;
    row[n - 2][m - 2] = row[n - 1][m - 2] = oc;
    row[n - 2][m - 3] = row[n - 1][m - 3] = c;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m - 1; j++)
            cout << (row[i][j] == 1 ? 'R' : 'B') << " ";
        cout << "\n";
    }
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < m; j++)
            cout << (col[i][j] == 1 ? 'R' : 'B') << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        solve();
    }
};