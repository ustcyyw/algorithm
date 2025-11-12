/**
 * @Time : 2024/9/25-2:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1883G2 找规律 二分
 */
/*
  * 对于两个给定的数组b和c 解决单一问题（easy 版本就是单一问题）
  * 两个数组排序 从右到左 如果b[i] <= c[i] 就删除b当前最小元素和a当前元素（和删最大元素效果一样）
  *
  * c中元素只改动一个，并且从1～m，该元素越来越大
  * 1. k肯定是单调不减的 因为c的元素只有变大的
  * 2. k的变化最多是1，因为只要把c[1]删掉 剩下的c的元素不变
  * 大不了无脑先将c[1]删掉就行
  * 因此可以先假设c[1] = 0，算出来k0
  * 当c[1]取1~m时 ki >= k0 但是可以计算最小的i使得 ki = k0 + 1
  * 根据这个分界点 将c数组分为两类 一类的答案是k0，另一类是k0 + 1
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5, mod = 998244353;
int T, n, m, a[N], b[N], c[N];

int cal(int v) {
    c[1] = v;
    for(int i = 2; i <= n; i++)
        c[i] = a[i];
    sort(c, c + n + 1);
    int cnt = 0;
    for(int i = n, j = n; i >= 1; i--) {
        if(c[i] >= b[j]) cnt++;
        else j--;
    }
    return cnt;
}

void solve() {
    sort(b, b + n + 1);
    int k0 = cal(0);
    int lo = 1, hi = m;
    while(lo < hi) {
        int mid = (lo + hi) >> 1, k1 = cal(mid);
        if(k1 == k0 + 1) hi = mid;
        else lo = mid + 1;
    }
    cout << (ll)(lo - 1) * k0 + (ll)(m - lo + 1) * cal(lo) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 2; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        solve();
    }
};