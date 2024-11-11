/**
 * @Time : 2024/3/28-10:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 最大1e14 数位和最大为 117，最小为1
  * 也就是说 mod的备选只有117 和的备选也只有117
  *
  * 截止第i位 和为sum 且对d取摸且余数为mod的数有 数位dp
  * 其中并不知道最终加和是多少 所以要枚举d
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, M = 13 * 9;
int n, m;
string s;

void solve() {
    vector<vector<vector<ll>>> cache;
    function<ll(int, int, int, int, bool, bool)> dfs = [&](int d, int i, int sum, int mod, bool is_num, bool limit) -> ll {
        if(i == n) return is_num && sum == d && mod == 0;
        if(is_num && !limit && cache[i][sum][mod] != -1) return cache[i][sum][mod];
        ll cnt = 0;
        if(!is_num) cnt = dfs(d, i + 1, 0, 0, false, false);
        int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
        for(int j = down; j <= up; j++) {
            int nm = (mod * 10 + j) % d;
            cnt += dfs(d, i + 1, sum + j, nm, true, limit && j == up);
        }
        if(is_num && !limit) cache[i][sum][mod] = cnt;
        return cnt;
    };
    ll res = 0;
    for(int d = 1; d <= m; d++) {
        cache.assign(n, vector(m + 1, vector(m + 1, -1ll)));
        res += dfs(d, 0, 0, 0, false, true);
    }
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    n = s.size(), m = n * 9;
    solve();
};