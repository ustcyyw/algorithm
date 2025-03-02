#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;

class Solution {
public:

    ll bmul(ll a, ll b, ll m) {  // 快速乘
        ull c = (ull) a * (ull) b - (ull) ((long double) a / m * b + 0.5L) * (ull) m;
        if (c < (ull) m) return c;
        return c + m;
    }

    ll qpow(ll x, ll p, ll mod) {  // 快速幂
        ll ans = 1;
        while (p) {
            if (p & 1) ans = bmul(ans, x, mod);
            x = bmul(x, x, mod);
            p >>= 1;
        }
        return ans;
    }

    bool Miller_Rabin(ll p) {  // 判断素数
        if (p < 2) return false;
        if (p == 2) return true;
        if (p == 3) return true;
        ll d = p - 1, r = 0;
        while (!(d & 1)) ++r, d >>= 1;  // 将d处理为奇数
        for (ll k = 0; k < 10; ++k) {
            ll a = rand() % (p - 2) + 2;
            ll x = qpow(a, d, p);
            if (x == 1 || x == p - 1) continue;
            for (int i = 0; i < r - 1; ++i) {
                x = bmul(x, x, p);
                if (x == p - 1) break;
            }
            if (x != p - 1) return false;
        }
        return true;
    }

    ll Pollard_Rho(ll x) {
        ll s = 0, t = 0;
        ll c = (ll) rand() % (x - 1) + 1;
        int step = 0, goal = 1;
        ll val = 1;
        for (goal = 1;; goal *= 2, s = t, val = 1) {  // 倍增优化
            for (step = 1; step <= goal; ++step) {
                t = (bmul(t, t, x) + c) % x;
                val = bmul(val, abs(t - s), x);
                if ((step % 127) == 0) {
                    ll d = gcd(val, x);
                    if (d > 1) return d;
                }
            }
            ll d = gcd(val, x);
            if (d > 1) return d;
        }
    }

// 质因数分解
    vector<ll> factor(ll n) {
        vector<ll> factors;
        if (n == 1) return factors;
        if (Miller_Rabin(n)) {
            factors.push_back(n);
            return factors;
        }
        ll d = Pollard_Rho(n);
        vector<ll> left = factor(d), right = factor(n / d);
        factors.insert(factors.end(), left.begin(), left.end());
        factors.insert(factors.end(), right.begin(), right.end());
        return factors;
    }
};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{1,2,2,2,2},{2,2,2,2,0},{2,0,0,0,0},{0,0,2,2,2},{2,0,0,2,0}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    vector<ll> ans = s.factor(4);
    for(int num : ans)
        cout << num << " ";
}
