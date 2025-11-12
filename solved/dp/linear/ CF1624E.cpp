/**
 * @Time : 2024/7/25-10:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1624E 思维 + 动态规划
 */
 /*
  * 长度为2/3的子串即可凑出来任意长度的子串
  * 如果能找到一个长度超过3的子串再其它号码中完整出现 大可将其拆分成多个长度为2/3的子串
  * 而一个长度超过3的子串没有在其它号码中完整出现，此时将其拆分得越细碎 在不同号码中去找每一个部分更容易找到
  * 因此 我们只需要考虑用长度为2/3的子串去覆盖即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, dp[N];
string s;
vector<vector<int>> ans;
unordered_map<string, vector<int>> mp;

bool solve() {
    dp[0] = 1;
    for(int i = 1; i <= m; i++) {
        if(dp[i - 1] == 0) continue;
        if(mp.count(s.substr(i, 2))) dp[i + 1] = 2;
        if(i + 2 <= m && mp.count(s.substr(i, 3))) dp[i + 2] = 3;
    }
    if(dp[m] == 0) return false;
    for(int i = m; i > 0; i -= dp[i]) {
        int j = i - dp[i] + 1;
        ans.push_back(mp[s.substr(j, dp[i])]);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        mp = {}, ans = {};
        fill(dp, dp + m + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> s;
            s = '.' + s + '.';
            for(int j = 1; j <= m - 1; j++) {
                mp[s.substr(j, 2)] = {j, j + 1, i};
                mp[s.substr(j, 3)] = {j, j + 2, i};
            }
        }
        cin >> s;
        s = '.' + s;
        if(!solve()) cout << "-1\n";
        else {
            reverse(ans.begin(), ans.end());
            cout << ans.size() << "\n";
            for(auto& p : ans) {
                cout << p[0] << " " << p[1] << " " << p[2] << "\n";
            }
        }
    }
};