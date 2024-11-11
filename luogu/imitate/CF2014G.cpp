/**
 * @Time : 2024/9/27-4:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2014G 模拟
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, m, k;
vector<vector<ll>> milks;

ll drink(stack<vector<ll>>& oldMilk, ll day, ll lastDay) {
    ll ans = 0, need = m; // 当前这天需要喝多少牛奶
    while(!oldMilk.empty() && day - oldMilk.top()[0] < k && day <= lastDay) {
        vector<ll>& cur = oldMilk.top();
        // 先考虑如果当天已经喝了一部分的情况
        if(need != m) {
            if(cur[1] < need) need -= cur[1], cur[1] = 0;
            else {
                cur[1] -= need, day++, ans++;
                need = m;
            }
        } else {
            // 计算当前牛奶最多能喝多少（总量、保质期、和允许喝到的天数限制）
            ll ddl = min(cur[0] + k - 1, lastDay); // 保质期和当前牛奶允许喝到的最后一天
            ll val = min(m * (ddl - day + 1), cur[1]);
            // 计算还能喝多少个整天 及不满整天剩下那天能喝多少
            ll t = val / m, mod = val % m;
            day += t, need = m - mod;
            cur[1] -= val, ans += t;
        }
        if(cur[1] == 0) oldMilk.pop();
    }
    return ans;
}

void solve() {
    ll ans = 0;
    stack<vector<ll>> oldMilk;
    for(int i = 0; i < n; i++) {
        // 当前天数、当前这些牛奶可以喝到哪天lastDay，lastDay + 1就是下一瓶牛奶来的日期了
        ll day = milks[i][0], lastDay = milks[i + 1][0] - 1;
        oldMilk.push(milks[i]);
        ans += drink(oldMilk, day, lastDay);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> k;
        milks = {};
        for(int i = 1, d, val; i <= n; i++) {
            cin >> d >> val;
            milks.push_back({d, val});
        }
        milks.push_back({INT_MAX, 0});
        sort(milks.begin(), milks.end());
        solve();
    }
};