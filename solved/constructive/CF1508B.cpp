/**
 * @Time : 2025/1/12-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1508B 1800 构造 找规律
 */
/*
 * n = 1    1组
n = 2    2组
(1,2) (2,1)
n = 3    4组
3 2 1
2 1 3
1 (2 3) (3 2)
n = 4   共8组
4 3 2 1
3 2 1 4
2 1 (3, 4) (4, 3)
1 (4 3 2) (3 2 4) (2 3 4) (2 4 3)

n = 5 一共是 1 + 1 + 2 + 4 + 8 = 16
5 4 3 2 1 (16)
4 3 2 1 5 (15)
3 2 1 (4, 5) (5, 4)       (13,14)
2 1 (5 4 3) (4 3 5) (3 4 5) (3 5 4)       (9,12)
1 (5 4 3 2) (4 3 2 5) ... 共8组 （1,8）

所以一共会有2 ^ (n - 1)组
如果k <= 2 ^ (n - 2), 开头数字是1
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, K, ans[N], p[64];

int init = []() -> int {
    for(ll i = 0, temp = 1; i <= 63; i++, temp *= 2)
        p[i] = temp;
    return 0;
}();

int find(int m, ll& k) {
    if(m >= 63) return 1;
    for(int i = 1; i <= m; i++) {
        ll cnt = i < m ? p[m - i - 1] : 1;
        if(cnt >= k) return i;
        k -= cnt;
    }
    return -1;
}

void dfs(int idx, int m, int base, ll k) {
    if(idx > n) return;
    int j = find(m, k), nb = base + j, nm = m - j;
    while(j > 0) {
        ans[idx] = base + j;
        j--, idx++;
    }
    dfs(idx, nm, nb, k);
}

void solve() {
    if(n <= 63 && K > p[n - 1]) {
        cout << "-1\n";
        return;
    }
    dfs(1, n, 0, K);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> K;
        solve();
    }
};