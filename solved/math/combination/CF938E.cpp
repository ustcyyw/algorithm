/**
 * @Time : 2025/3/23-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF938E 2300 数学 组合数学 贡献法
 */
/*
  * 从贡献的角度来看
  * 最大元素 在任何排列中贡献都是0 因为没有数可以除非它的加和操作
  * 第二大元素 只要num1不在其前面即可
  * 但本题有相同大小的数字 但是依旧按不同排列计算
  * 假设 >= 当前数字的数一共有c个 这c个数字只能放在当前数字的后面
  * 假设当前数字所在的位置是i, 那么其后面还有 n - i个位置 一共有C(n - i, c)个排列
  * 这个数字可以出现在位置1,2,...,n-c
  * 因此总的方案数是 sum{C(n - i, c), for i in range [1,n-c]} * A(c, c) * A(n-c-1,n-c-1)
  * 其中A(c, c)是表示 >= 当前数字的数，都放在了当前数的右边 但是其内部是可以任意排列的
  * A(n-c-1,n-c-1)是表示 除了c个数和当前数安排后 还剩下n - c - 1个位置 这些位置的数可以任意排列
  * 利用组合数公式 C(k,c) = C(k + 1, c + 1) - C(k, c + 1)
  * 裂项相消可得 sum{C(n - i, c), for i in range [1,n-c]}
  * 所以方案总数是 way = C(n, c + 1) * A(c, c) * A(n-c-1,n-c-1)
  * 再考虑到当前这个数值的数出现的次数 以及这个值本身 就能计算某个值贡献的答案了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 15, mod = 1e9 + 7;
int T, n;

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

ll A(int n, int a) {
    return x[n] * invF[n - a] % mod;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
//    T = 1;
    cin >> n;
    map<int, int> map;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        map[num]++;
    }
    ll ans = 0, sum = 0;
    for(auto it = map.rbegin(); it != map.rend(); it++) {
        int cc = it->second;
        sum += cc;
        ll way = C(n, sum) * A(sum - 1, sum - 1) % mod * A(n - sum, n - sum) % mod;
        ll temp = way * cc % mod * it->first % mod;
        if(it != map.rbegin()) ans = (ans + temp) % mod;
    }
    cout << ans;
}