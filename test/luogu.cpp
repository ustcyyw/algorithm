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
typedef long double ld;
const int N = 1e6 + 15, M = 30;
ll n, s;

bool check(ll num) {
    ll cnt = 0, temp = num;
    while(temp) {
        cnt += temp % 10;
        temp /= 10;
    }
    return num - cnt >= s;
}

ll solve() {
    if(s >= n) return 0;
    int m = to_string(s).size();
    ll t = min(n, s + m * 9);
    ll ans = 0;
    for(ll num = s + 1; num <= t; num++)
        ans += check(num);
    return ans + n - t;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    cout << solve();
}