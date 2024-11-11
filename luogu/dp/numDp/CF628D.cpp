/**
 * @Time : 2024/3/22-10:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 数位dp 注意余数的传递处理
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, MOD = 1e9 + 7;
int m, d;
string l, r;

ll count(string& s) {
    int n = s.size();
    vector<vector<vector<ll>>> cache(2, vector(n, vector(m, -1ll)));
    // flag 为true表示当前位是偶数位
    function<ll(int, int, bool, bool, bool)> dfs =
            [&](int i, int mod, bool flag, bool is_num, bool limit) -> ll {
                if(i == n) return is_num && mod == 0;
                if(!limit && is_num && cache[flag][i][mod] != -1) return cache[flag][i][mod];
                ll cnt = 0;
                if(!is_num) cnt = dfs(i + 1, 0, false, false, false);
                int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
                if(flag) {
                    if(d > up || d < down) up = -1; // 偶数位置 无法放置d 那么就设置up=-1，不进入循环
                    else down = d, up = d;
                }
                for(int j = down; j <= up; j++) {
                    if(!flag && j == d) continue;
                    int nm = (mod * 10 + j) % m;
                    cnt += dfs(i + 1, nm, !flag, true, limit && j == (s[i] - '0'));
                }
                cnt %= MOD;
                if(!limit && is_num)
                    cache[flag][i][mod] = cnt;
                return cnt;
            };
    return dfs(0, 0, false, false, true);
}

int check(string& s) {
    int mod = 0;
    for(int i = 0; i < s.size(); i++) {
        int num = s[i] - '0';
        mod = (mod * 10 + num) % m;
        if(i % 2 == 0 && num == d) return 0;
        if(i % 2 == 1 && num != d) return 0;
    }
    return mod == 0;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> m >> d;
    cin >> l >> r;
    ll ans = count(r) - count(l) + check(l);
    ans = (ans % MOD + MOD) % MOD;
    cout << ans << "\n";
};