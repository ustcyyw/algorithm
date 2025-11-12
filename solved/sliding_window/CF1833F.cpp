/**
 * @Time : 2024/3/18-11:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 滑动窗口
 * 要选m个数且是不同数字 而且要求两两之间只差m 说明这是连续的m个值
 * 先将原数组按数字归类 然后找长度为m的序列 首位元素相减为m-1
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m;
ll inv[N];

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

int init = []() -> int {
    for(int i = 1; i < N; i++)
        inv[i] = qPow(i, mod - 2);
    return 0;
}();

void solve() {
    map<int, int> map;
    for (int i = 0, num; i < n; i++) {
        cin >> num;
        map[num]++;
    }
    vector<pair<int, int>> arr;
    for (auto &p: map)
        arr.push_back(p);
    ll ans = 0, mul = 1ll;
    for (int lo = 0, hi = 0; hi < arr.size(); hi++) {
        mul = mul * arr[hi].second % mod;
        if (hi - lo + 1 > m) {
            mul = mul * inv[arr[lo].second] % mod;
            lo++;
        }
        if (hi - lo + 1 == m && arr[hi].first - arr[lo].first == m - 1)
            ans = (ans + mul) % mod;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        solve();
    }
};