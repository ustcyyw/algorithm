/**
 * @Time : 2024/5/14-9:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1176F dp + 贪心
 */
/*
 * dp[i][j]:截止第i轮,累积牌数（对10取余）为j的最大伤害
 *
 * 每轮排 最多可以出3张牌
 * 3张牌的最大值：只有3个1
 * 2张牌的最大值：1+1，1+2
 * 1张牌的最大值：1 2 3
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, c, d;

vector<vector<ll>> pick() {
    cin >> k;
    vector<int> cc[4];
    for(int i = 1; i <= k; i++) {
        cin >> c >> d;
        cc[c].push_back(d);
    }
    for(int i = 1; i <= 3; i++)
        sort(cc[i].begin(), cc[i].end());
    int n1 = cc[1].size(), n2 = cc[2].size(), n3 = cc[3].size();
    vector<vector<ll>> cards;
    // 选择三张牌
    if(n1 >= 3)
        cards.push_back({3, (ll)cc[1][n1 - 1] + cc[1][n1 - 2] + cc[1][n1 - 3], cc[1][n1 - 1]});
    // 选择两张牌
    if(n1 >= 2)
        cards.push_back({2, cc[1][n1 - 1] + cc[1][n1 - 2], cc[1][n1 - 1]});
    if(n1 >= 1 && n2 >= 1)
        cards.push_back({2, cc[1][n1 - 1] + cc[2][n2 - 1], max(cc[1][n1 - 1], cc[2][n2 - 1])});
    // 选择1张牌
    ll t1 = n1 >= 1 ? cc[1].back() : -1;
    ll t2 = n2 >= 1 ? cc[2].back() : -1;
    ll t3 = n3 >= 1 ? cc[3].back() : -1;
    ll mv = max({t1, t2, t3});
    cards.push_back({1, mv, mv});
    return cards;
}

// dp[i][j]:截止第i轮,累积牌数（对10取余）为j的最大伤害
void solve() {
    vector<vector<ll>> dp(n + 1, vector(10, -1ll));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        vector<vector<ll>> cards = pick();
        for(int j = 0; j <= 9; j++) {
            dp[i][j] = dp[i - 1][j]; // 表示本轮一张牌都不出
            for(auto& t : cards) {
                ll pre = (j - t[0] + 10) % 10;
                ll sum = t[1], mv = t[2], val = j - t[0] < 0 ? sum + mv : sum;
                if(dp[i - 1][pre] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][pre] + val);
                }
            }
        }
    }
    ll ans = 0;
    for(int i = 0; i < 10; i++)
        ans = max(dp[n][i], ans);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    solve();
};