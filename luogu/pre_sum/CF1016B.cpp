/**
 * @Time : 2025/4/6-10:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1016B 1300 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 15, M = 30;
ll n, m, q, sum[N];
string s, t;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> q >> s >> t;
    s = '.' + s;
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1];
        sum[i] += s.substr(i, m) == t;
    }
    for(int i = 1, l, r; i <= q; i++) {
        cin >> l >> r;
        if(r - l + 1 < m) cout << "0\n";
        else {
            int hi = r - m + 1;
            cout << sum[hi] - sum[l - 1] << "\n";
        }
    }
}