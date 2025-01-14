/**
 * @Time : 2025/1/13-8:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1750D 1800 数学 数论 组合数学 容斥原理
 */
 /*
  * b1 = a1
  * 对于a[i-1]和a[i]来说 a[i]必须是a[i-1]的因子 因为是gcd运算
  * 记pre = a[i - 1] / a[i], 那么所选的b[i]除了含有a[i]因子外 就不能含有任何pre的质因子
  * 否则的话gcd[b[1]...b[i]] > a[i]了
  * 所以要看m个数中 有多少个数含有a[i], 且不能含有任何pre的质因子
  * 含有a[i]很简单，一共有 m / a[i]个数，在这些数中 不能含有任何pre的质因子
  * pre的质因子有好几个 不能含任何一个 于是想到容斥定理计算
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, m, nums[N];

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

void fac(set<ll>& st, vector<ll>& ans, ll x) {
    if(x == 1) return;
    if (Miller_Rabin(x)) {
        if(!st.count(x))
        ans.push_back(x), st.insert(x);
        return;
    }
    ll p = x;
    while (p >= x) p = Pollard_Rho(x);
    while ((x % p) == 0) x /= p;
    fac(st, ans, x), fac(st, ans, p);
}

vector<ll> get_prime_factor(ll num) {
    srand((unsigned) time(NULL));
    set < ll > set;
    vector<ll> ans;
    fac(set, ans, num);
    return ans;
}

ll cal(vector<ll> &f, ll total) {
    ll ans = 0;
    int n = f.size(), u = (1 << n) - 1;
    for (int s = 1; s <= u; s++) {
        ll num = 1, cnt = 0;
        for (int j = 0; j < n; j++) {
            if ((1 << j) & s)
                num *= f[j], cnt++;
        }
        ll temp = total / num;
        if (cnt % 2 == 1) ans = (ans + temp) % mod;
        else ans = (ans - temp + mod) % mod;
    }
    return ans;
}

ll solve() {
    if (nums[1] > m) return 0;
    ll ans = 1;
    for (int i = 2; i <= n; i++) {
        if (nums[i - 1] % nums[i] != 0) return 0;
        if (nums[i - 1] == 1) {
            ans = ans * m % mod;
            continue;
        }
        ll pre = nums[i - 1] / nums[i];
        vector<ll> f = get_prime_factor(pre);
        ans = ans * (m / nums[i] - cal(f, m / nums[i]) + mod) % mod;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};