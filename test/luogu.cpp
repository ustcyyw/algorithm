/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000 + 5, mod = 998244353;
int T, n, q, val[N][N], mv[N][N], pre[N][N];

void init() {
    for(int len = 2; len <= n; len++) {
        for(int i = 0, j = i + len - 1; j < n; i++, j++) {
            val[i][j] = val[i][j - 1] ^ val[i + 1][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            mv[i][j] = j == i ? val[i][j] : max(val[i][j], mv[i][j - 1]);
        }
    }
    for(int r = n - 1; r >= 0; r--) {
        for(int l = r, v = 0; l >= 0; l--) {
            v = max(v, mv[l][r]);
            pre[l][r] = v;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> val[i][i];
        init();
        cin >> q;
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << pre[l - 1][r - 1] << "\n";
        }
    }
};