/**
 * @Time : 2024/8/19-2:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1744E2 数学
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 9;
typedef long long ll;
int T, n, a, b, c, d;
ll x, y;

vector<ll> get_factor(ll num) {
    vector<ll> ans;
    for(ll i = 1; i * i <= num; i++) {
        if(num % i == 0) {
            ans.push_back(i);
            if(i * i != num) ans.push_back(num / i);
        }
    }
    return ans;
}

bool solve() {
    ll t = (ll)a * b;
    vector<ll> fa = get_factor(a), fb = get_factor(b);
    for(ll& ai : fa) {
        for(ll& bi : fb) {
            ll x_base = ai * bi, y_base = t / x_base;
            x = c / x_base * x_base, y = d / y_base * y_base;
            if(x > a && y > b) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> a >> b >> c >> d;
        if(!solve()) cout << "-1 -1\n";
        else cout << x << " " << y << "\n";
    }
};