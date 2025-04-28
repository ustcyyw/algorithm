/**
 * @Time : 2025/4/27-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1027B 1200 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 5, mod = 998244353;
ll T, n, q;

ll get_rank(int x, int y) {
    if(n % 2 == 0) return n / 2 * (x - 1) + (y + 1) / 2;
    ll line = (x - 1) / 2 * n, m = (x - 1) % 2;
    if(m == 0) return line + (y + 1) / 2;
    if((x + y) % 2 == 0) {
        return line + (y + 1) / 2 + (n + 1) / 2;
    } else
        return line + (y + 1) / 2 + (n - 1) / 2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    ll base = n * n / 2 + n % 2;
    for(int i = 1, x, y; i <= q; i++) {
        cin >> x >> y;
        ll pos = x + y, ans = 0, rank = get_rank(x, y);
        if(pos % 2 == 0) ans = rank;
        else ans = base + rank;
        cout << ans << "\n";
    }
}