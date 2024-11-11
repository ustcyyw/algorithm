/**
 * @Time : 2024/3/14-9:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
ll b, s, c, cb, cs, cc, mb, ms, mc, r;
string str;

ll cal(ll n, ll cnt, ll have, ll money) {
    if(n * cnt <= have) return 0;
    return (n * cnt - have) * money;
}

void solve() {
    b = s = c = 0;
    for(char t : str) {
        if(t == 'B') b++;
        if(t == 'S') s++;
        if(t == 'C') c++;
    }
    ll lo = 0, hi = 1e12 + 1e5;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(cal(mid, b, cb, mb) + cal(mid, s, cs, ms) +  cal(mid, c, cc, mc) <= r) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> str;
    cin >> cb >> cs >> cc >> mb >> ms >> mc >> r;
    solve();
};