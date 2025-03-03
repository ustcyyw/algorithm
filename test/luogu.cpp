/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
ll T, a, b;

multiset<ll> get_factor(ll num) {
    multiset<ll> st;
    for(int i = 2; i <= sqrt(num); i++) {
        while(num % i == 0) {
            st.insert(i);
            num /= i;
        }
    }
    if(num > 1) st.insert(num);
    return st;
}

ll dfs(multiset<ll>& st, ll k2) {
    if(st.empty() || k2 == 1) return k2;
    ll cnt = LONG_LONG_MAX, num = -1;
    for(ll t : st) {
        if(cnt > k2 % t)
            cnt = k2 % t, num = t;
    }
    st.erase(st.find(num));
    return cnt + dfs(st, (k2 - cnt) / num);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b;
    ll g0 = gcd(a, b);
    ll k1 = a / g0, k2 = b / g0;
    multiset<ll> st = get_factor(k1);
    cout << dfs(st, k2);
}