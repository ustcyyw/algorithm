/**
 * @Time : 2025/3/15-9:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : ABC397D 数学 数论 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef unsigned long long ull;
const int N = 3e5 + 5, mod = 1e9 + 7;
long long n;

bool check(ll diff, ll x, ll A) {
    if(x % A != 0 || x <= 0) return false;
    x /= A;
    ll y = x - diff;
    if(y <= 0) return false;
    cout << (long long)x << " " << (long long)y;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(ll diff = 1; diff <= 1e6; diff++) {
        if(n % diff != 0) continue;
        // x - y = diff, y = x - diff
        ll f = n / diff;
        ll a = 3, b = -3 * diff, c = diff * diff - f;
        ll temp = b * b - 4 * a * c;
        if(temp < 0) continue;
        if((ll)sqrt(temp) * (ll)sqrt(temp) != temp) continue;
        ll x1 = -b - (ll)sqrt(temp), x2 = -b + (ll)sqrt(temp);
        if(check(diff, x1, 2 * a) || check(diff, x2, 2 * a)) return 0;
    }
    cout << -1;
}