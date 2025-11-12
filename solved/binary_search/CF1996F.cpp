/**
 * @Time : 2024/11/30-11:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1996F 1900 二分 + 贪心
 */
 /*
  * 肯定优先选最大的值来加 但是k很大 按贪心来模拟肯定不行
  * 答案被找到的时候 最后一个被加的数是固定的 那么可以考虑先找到这个数 val
  * 那么任何一个ai能被用几次 就能被确定 也就能直接按等差数列求和
  *
  * 找val 可以使用二分答案 val需要满足每个ai的可能次数之和 >= k，并且是最大满足这个条件的数
  * 找到val后计算每个ai的贡献值即可，但是要注意example1的情况
  * 会有几个ai最终都能用到val，导致这样都计算的话 总的得分操作次数 > k
  * 于是可以先用val + 1去算，最后不足k的用val补足即可。
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, k, a[N], b[N];

ll count(ll num1, ll num2, int val) {
    if(num1 < val) return 0;
    return (num1 - val) / num2 + 1;
}

bool check(int val) {
    ll cnt = 0;
    for(int i = 1; i <= n; i++) {
        cnt += count(a[i], b[i], val);
        if(cnt >= k) return true;
    }
    return false;
}

void solve() {
    int lo = 0, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        ll cnt = count(a[i], b[i], lo + 1);
        ans += (a[i] - (cnt - 1) * b[i] + a[i]) * cnt / 2;
        k -= cnt;
    }
    ans += (ll)lo * k;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        solve();
    };
};