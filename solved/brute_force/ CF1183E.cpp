/**
 * @Time : 2024/5/15-3:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1183E 贪心 + 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k;
string s;
unordered_set<string> sets[105];

void solve() {
    int ans = 0;
    sets[n].insert(s);
    k -= 1;
    for(int i = n - 1; i >= 0 && k > 0; i--) {
        for(string t : sets[i + 1]) {
            for(int j = 0; j < i + 1; j++) {
                string pre = t.substr(0, j), suf = t.substr(j + 1, i - j);
                sets[i].insert(pre + suf);
            }
        }
        int cnt = min(k, (int)sets[i].size());
        k -= cnt, ans += (n - i) * cnt;
    }
    cout << (k > 0 ? - 1 : ans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    cin >> s;
    solve();
};