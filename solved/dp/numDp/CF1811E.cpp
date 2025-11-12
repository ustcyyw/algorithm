/**
 * @Time : 2023/12/23-3:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
ll T, k;

long long count(string& s) {
    int n = s.size();
    vector<ll> cache(n, -1);
    function<ll(int, bool, bool)> dfs = [&](int i, bool limit, bool is_num) -> ll {
        if(i == n) return is_num;
        if(!limit && is_num && cache[i] != -1) return cache[i];
        ll cnt = 0;
        if(!is_num) cnt = dfs(i + 1, false, false);
        int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
        for(int j = down; j <= up; j++) {
            if(j == 4) continue;
            cnt += dfs(i + 1, limit && j == up, true);
        }
        if(!limit && is_num) cache[i] = cnt;
        return cnt;
    };
    return dfs(0, true, false);
}

void solve() {
    ll lo = 1, hi = pow(10, to_string(k).size() + 1);
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        string s = to_string(mid);
        if(count(s) >= k) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> k;
        solve();
    }
}