/**
 * @Time : 2024/6/20-8:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1296C
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, T = 1e6;
typedef long long ll;
int q, n;
string s;

void solve() {
    unordered_map<ll, int> map;
    map[0] = 0;
    int ans = n + 1, l, r;
    for(int i = 1, t1 = 0, t2 = 0; i <= n; i++) {
        char c = s[i];
        if(c == 'L') t1++;
        else if(c == 'R') t1--;
        else if(c == 'U') t2++;
        else t2--;
        ll key = (ll)t1 * T + t2;
        if(map.count(key)) {
            int len = i - map[key];
            if(len < ans) ans = len, l = map[key] + 1, r = i;
        }
        map[key] = i;
    }
    if(ans == n + 1) cout << -1 << "\n";
    else cout << l << " " << r << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> q;
    while(q-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        solve();
    }
};