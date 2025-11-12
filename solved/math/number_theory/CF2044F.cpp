/**
 * @Time : 2024/12/16-11:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2044F 数学 暴力枚举
 */
 /*
  * 注意到 矩阵的和就是 suma * sumb
  * 并且观察到abs(x) < 2e5 因子数目并不多
  * 某一次操作实际上就是将 suma - a[r], sumb - b[c]， 然后相乘 必须两个数都是x的因子
  * 所有可以先预处理删除某个a中元素的一系列suma，同理b
  * 然后暴力枚举x的两个因子 看看是否刚好在一系列的数组和中
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = (int)sqrt(N);
ll T, n, m, q, a[N], b[N], x;
unordered_set<ll> st1, st2;

unordered_set<ll> init(ll total, ll* arr) {
    for(int i = 1; i <= total; i++)
        cin >> arr[i];
    ll sum = accumulate(arr + 1, arr + total + 1, 0ll);
    unordered_set<ll> set;
    for(int i = 1; i <= total; i++)
        set.insert(sum - arr[i]);
    return set;
}

bool cal(int f1, int f2) {
    return (st1.count(f1) && st2.count(f2)) || (st1.count(f2) && st2.count(f1));
}

bool check() {
    for(int i = 1; i <= sqrt(abs(x)); i++) {
        if(x % i != 0) continue;
        int j = abs(x) / i;
        if(x > 0 && (cal(i, j) || cal(-i, -j))) return true;
        if(x < 0 && (cal(-i, j) || cal(i, -j))) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> q;
        st1 = init(n, a), st2 = init(m, b);
        for(int i = 1; i <= q; i++) {
            cin >> x;
            cout << (check() ? "YES" : "NO") << "\n";
        }
    }
};