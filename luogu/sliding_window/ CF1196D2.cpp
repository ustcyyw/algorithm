/**
 * @Time : 2024/5/17-8:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
int T, n, m, mod, k, idx[3] = {1, 2, 3};
string s, temp[3] = {"RGB","GBR","BRG"};

int get_add(string& t, int hi) {
    int add = 0;
    if(mod > 1)  add += s[hi + 1] == t[1];
    if(mod > 0) add += s[hi] == t[0];
    return add;
}

int cal(string& t, int start) {
    int lo = start, hi = start, cnt = 0, ans = INT_MAX;
    if(k < 3) ans = k - get_add(t, start);
    while(hi + mod - 1 <= n) {
        if(k >= 3) {
            if(hi + 2 > n) break;
            for(int j = 0; j < 3; j++)
                if(t[j] == s[hi++]) cnt++;
        } else hi++;
        if(k < 3) lo++;
        else if((hi - lo) / 3 > m) {
            for(int j = 0; j < 3; j++)
                if(t[j] == s[lo++]) cnt--;
        }
        if(hi + mod - 1 > n) break;
        ans = min(ans, k - (cnt + get_add(t, hi)));
    }
    return ans;
}

void solve() {
    mod = k % 3, m = k / 3;
    int ans = INT_MAX;
    for(int start : idx) {
        for(string& t : temp)
            ans = min(ans, cal(t, start));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        cin >> s;
        s = '.' + s;
        solve();
    }
};