/**
 * @Time : 2024/7/8-3:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1475E 贪心 组合数学
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1000 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, cnt[N];

long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

// 预处理阶乘 和 阶乘的逆元
long long x[N], invF[N];
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
long long C(int n, int a) {
    return x[n] * invF[n - a] % mod * invF[a] % mod;
}

ll solve() {
    for(int i = n; i >= 1 && k; i--) {
        if(k <= cnt[i]) {
            return C(cnt[i], k);
        } else k -= cnt[i];
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        memset(cnt, 0, sizeof(cnt));
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            cnt[num]++;
        }
        cout << solve() << "\n";
    }
};