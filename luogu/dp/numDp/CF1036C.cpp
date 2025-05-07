/**
 * @Time : 2025/5/6-9:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1036C 1900 动态规划 数位dp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
ll T, l, r;

// dfs(i, cnt, limit, is_num): 截止i位置，前面至多使用了cnt个非0数字的方案数
ll solve(ll n) {
    string s = to_string(n);
    int m = s.size();
    vector<vector<ll>> dp(m, vector(4, -1ll));
    function<ll(int, int, bool, bool)> dfs = [&](int i, int cnt, bool limit, bool is_num) -> ll {
        if(i == m) return is_num;
        if(!limit && is_num && dp[i][cnt] != -1) return dp[i][cnt];
        ll ans = 0;
        if(!is_num) ans = dfs(i + 1, cnt, false, false);
        int up = limit ? s[i] - '0' : 9, down = is_num ? 0 : 1;
        for(int j = down; j <= up; j++) {
            if(j > 0 && cnt + 1 <= 3) ans += dfs(i + 1, cnt + 1, j == up && limit, true);
            if(j == 0) ans += dfs(i + 1, cnt, j == up && limit, true);
        }
        if(!limit && is_num) dp[i][cnt] = ans;
        return ans;
    };
    return dfs(0, 0, true, false);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> l >> r;
        cout << solve(r) - solve(l - 1) << "\n";
    }
}