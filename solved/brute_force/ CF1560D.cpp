/**
 * @Time : 2024/7/13-2:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1560D 暴力枚举 贪心
 */
 /*
  * 暴力枚举可能的2的幂次
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2005, mod = 1e9 + 7;
typedef long long ll;
int T, n;
string ss[64], t;

int init = []() -> int {
    for(ll i = 0, num = 1; i < 64; i++, num *= 2)
        ss[i] = to_string(num);
    return 0;
}();

int cal(string& s) {
    int j = 0;
    for(int i = 0; i < t.size(); i++) {
        if(t[i] == s[j]) j++;
    }
    return t.size() - j + s.size() - j;
}

void solve() {
    int ans = INT_MAX;
    for(int i = 0; i < 64; i++) {
        ans = min(ans, cal(ss[i]));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> t;
        solve();
    }
};