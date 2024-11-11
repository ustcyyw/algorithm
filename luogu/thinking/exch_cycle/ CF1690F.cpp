/**
 * @Time : 2024/7/17-10:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1690F
 */
 /* 给定的是排列 就会出现置换环
  * 置换环 同一个环里的字母经过一定次数的交换会恢复原状
  * 找不同置换环的交换次数 求lcm
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, p[205], marked[205];
string s;

ll exch_cycle(int start) {
    string t;
    t.push_back(s[start]), marked[start] = 1;
    for(int i = p[start]; i != start; i = p[i])
        t.push_back(s[i]), marked[i] = 1;
    int m = t.size();
    string d = t + t;
    for(int i = 1; i <= m; i++) {
        if(d.substr(i, m) == t)
            return i;
    }
    return 1;
}

void solve() {
    ll ans = 1;
    for(int i = 1; i <= n; i++) {
        if(!marked[i]) {
            ll t = exch_cycle(i);
            ans = lcm(ans, t);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        fill(marked, marked + n + 1, 0);
        for(int i = 1; i <= n; i++)
            cin >> p[i];
        solve();
    }
};