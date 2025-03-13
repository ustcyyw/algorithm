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
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k;
map<int, int> mp;
vector<int> arr;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
ll x[N], invF[N];
int init = []() -> int {
    x[0] = 1;
    invF[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        x[i] = x[i - 1] * i % mod;
        invF[i] = qPow(x[i], mod - 2);
    }
    return 0;
}();

// 组合数 C(n,a) n个元素取a个
ll C(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

bool check(int num) {
    while(num > 0) {
        if(num % 10 != 4 && num % 10 != 7) return false;
        num /= 10;
    }
    return true;
}

void solve() {
    int m = arr.size(), K = min(m, k);
    vector<vector<ll>> dp(m + 1, vector(K + 1, 0ll));
    dp[0][0] = 1;
    for(int i = 1; i <= m; i++) {
        int cnt = arr[i - 1];
        dp[i][0] = 1;
        for(int j = 1; j <= K; j++)
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * cnt % mod) % mod;
    }
    int total = accumulate(arr.begin(), arr.end(), 0), noTotal = n - total;
    ll ans = 0;
    // 枚举幸运数字构成的子序列的长度 再加上非幸运数字的即可
    for(int cnt = 0; cnt <= K; cnt++) {
        int oc = k - cnt;
        if(oc <= noTotal)
            ans = (ans + dp[m][cnt] * C(noTotal, oc) % mod) % mod;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(check(num)) mp[num]++;
        }
        for(auto& p : mp)
            arr.push_back(p.second);
        solve();
    }
}