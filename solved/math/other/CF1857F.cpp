/**
 * @Time : 2024/2/3-3:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * a + b = x, a * b = y
 * b = x - a, a * (x - a) = y
 * 整理得 a ^ 2 - xa + y = 0
 * 根据求根公式 a = x + sqrt(x^2 - 4y) / 2
 * 因为a和b都是整数 首先要求 x^2 + 4y 是一个完全平方数。另外要求 x和sqrt(x^2 + 4y)的奇偶性质一致
 * 另外 a和b完全是对称的。因此只要求出其中一个根 另外一个根就是b
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, nums[N];
map<ll, ll> mp;

bool check(ll x, ll y) {
    ll t = x * x - 4 * y, d = (long long)sqrt(t);
    if(d * d != t) return false;
    return (x % 2 + d % 2) % 2 == 0; // 保持奇偶性一致
}

ll count(ll a, ll b) {
    if(a == b) return mp[a] * (mp[a] - 1) / 2;
    return mp[a] * mp[b];
}

void solve() {
    cin >> m;
    ll x, y;
    for(int i = 0; i < m; i++) {
        cin >> x >> y;
        if(!check(x, y)) {
            cout << 0 << " ";
            continue;
        }
        ll d =  (ll)sqrt(x * x - 4 * y);
        ll a1 = (x + d) / 2, b1 = x - a1, cnt = count(a1, b1);
        cout << cnt << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        mp = {};
        for(int i = 0; i < n; i++) {
            cin >> nums[i];
            mp[nums[i]]++;
        }
        solve();
    }
};