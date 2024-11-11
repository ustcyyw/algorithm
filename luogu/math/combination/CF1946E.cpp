/**
 * @Time : 2024/3/26-5:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 排列组合
  * pre[m1] = suf[1]，这个索引对应的值是最大值
  * 放在最大值pre[m1]左边的数一共有 pre[m1] - 1 个，这些数的绝对大小没有意义
  * 因此从除去最大值的m-1个数中挑出来即可。
  * 先考虑pre[m1 - 1]，现在他是pre[m1]左边最大的数
  * 因为其右边只有pre[m1]比他大，且它大于它左边的数，那就唯一确定了
  * 在pre[m1 - 1]和pre[m1]确定的情况下，其中间还有(pre[i] - pre[i - 1] - 1)个数不确定
  * 从pre[m1] - 2个数中挑出来 并进行全排列。
  * 为什么是pre[m1] - 2，因为左边一共有pre[m1] - 1个数，而且pre[m1 - 1]唯一确定
  * 于是只剩pre[m1] - 2个数可选
  * 然后剩余可选的数就得再减少pre[i] - pre[i - 1] - 1个
  * 接下来pre[m1 - 2]就变成未排列的数中最大的了 以此类推
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, m, m1, m2, pre[N], suf[N];
ll mul[N], inv[N];

long long qPow(long long x, long long y) {
    long long ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}

int init = []() -> int {
    mul[0] = 1;
    inv[0] = qPow(1, mod - 2);
    for (int i = 1; i < N; i++) {
        mul[i] = mul[i - 1] * i % mod;
        inv[i] = qPow(mul[i], mod - 2);
    }
    return 0;
}();

// C 组合数板子
long long C(int n, int a) {
    return mul[n] * inv[n - a] % mod * inv[a] % mod;
}

// A 排列数板子
long long A(int n, int a) {
    return mul[n] * inv[n - a] % mod;
}

ll solve() {
    if(suf[1] != pre[m1] || pre[1] != 1 || suf[m2] != m) return 0;
    ll ans = C(m - 1, pre[m1] - 1);
    // 最大值左边的排列
    for(int i = m1, cnt = pre[m1] - 1; i > 1; i--) {
        if(--cnt == 0) break; // 当前最大的那个数 要放在pre[i - 1]位置处
        if(pre[i] - pre[i - 1] - 1)
            ans = ans * A(cnt, pre[i] - pre[i - 1] - 1) % mod;
        cnt -= pre[i] - pre[i - 1] - 1; // 抽取了之后 更新剩余备选的数
    }
    // 最大值右边的排列
    for(int i = 1, cnt = m - suf[1]; i < m2; i++) {
        if(--cnt == 0) break; // 当前最大的那个数 suf[i + 1]位置处
        if(suf[i + 1] - suf[i] - 1)
            ans = ans * A(cnt, suf[i + 1] - suf[i] - 1) % mod;
        cnt -= suf[i + 1] - suf[i] - 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> m >> m1 >> m2;
        for(int i = 1; i <= m1; i++)
            cin >> pre[i];
        for(int i = 1; i <= m2; i++)
            cin >> suf[i];
        cout << solve() << "\n";
    }
};
