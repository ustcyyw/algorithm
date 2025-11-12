/**
 * @Time : 2025/4/1-5:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF985D 2100 二分答案 数学
 */
/*
  * 假设有cnt个柱子 最高的柱子为v，v <= cnt
  * 要达到高度v，需要占用v个格子，还剩下 cnt - v个格子
  * 左端的最小高度为 v - (cnt - v) = 2v - cnt
  * 2v - cnt <= h，v <= (cnt + h) / 2
  * 所以 v = min(cnt, (cnt + h) / 2)
  * 去掉v之后 两个等差数列求和 1 + 2 + ... v 和 h, h+1 ... h+cnt-v-1 一共cnt-v个
  * (v + 1) * v / 2, (h + h+cnt-v-1) * (cnt - v) / 2
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 15, M = 30;
ll n, h;

bool check(ll cnt) {
    ll v = min(cnt, (cnt + h) / 2);
    if(v >= 2e9) return true; // v大于这个值 sum1 > 1e18了 一定可以
    ll sum1 = (v + 1) * v / 2;
    ll sum2 = cnt - v > 0 ? (h + h + cnt - v - 1) * (cnt - v) / 2 : 0;
    return sum1 + sum2 >= n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> h;
    ll lo = 1, hi = n;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo;
}