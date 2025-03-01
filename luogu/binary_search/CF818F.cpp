/**
 * @Time : 2025/2/28-12:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF818F 2100 贪心 二分答案
 */
 /*
  * 假设一开始都是桥 共有n-1个桥 逐渐加边
  * 如何加边才能使剩下的桥尽可能多呢
  * 假如是个星型图或者一条链子 画图看
  * 1. 肯定是选两个不相邻的点 连起来 桥-2，增加1条边
  * 2. 再选一个点，它和step1中连成一体的三个点中其中一个相邻 和另外两个点连起来 桥-1，增加2条边
  * 3. 再选一个点，它和step2中连成一体的四个点中其中一个相邻 和另外三个点连起来 桥-1，增加3条边
  * ...
  * 这样每次花费一条桥边 就能新增更多的边
  * 但是临界值在哪 不清楚 所以考虑二分 找到要将多少个点变成强连通分量
  * 找到最大的cnt 使得cnt个点两两都有一条边链接 其它点与这些点通过桥连接点情况下 满足条件
  * 找到cnt后再计算总边数即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll T, n;

// 找到最大的cnt 使得cnt个点两两都有一条边链接 其它点与这些点通过桥连接点情况下 满足条件
bool check(ll cnt) {
    ll bridge = n - cnt, total = (cnt - 1) * cnt / 2;
    return bridge >= total;
}

void solve() {
    ll lo = 1, hi = n;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    ll ans = n - lo + (lo - 1) * lo / 2;
    ll temp = lo + 1 <= n ? n - lo - 1 : 0;
    ans = max(ans, temp * 2);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        solve();
    }
}