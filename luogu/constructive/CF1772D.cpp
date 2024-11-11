/**
 * @Time : 2024/6/11-8:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1772D 构造 + 贪心
 */
 /*
  * 当前数后后面的数 进行abs(ai - x)的变换后保持升序
  * ai != aj 则会对x的取值范围进行限制
  * 并且举例子发现 aj与ai的差最小时 这个限制最严格
  * 因此对于每个ai都要找到其后续最接近它的一大一小两个数 然后得到x的限制条件
  * 一旦x的上限下限矛盾了 说明找不到这样的x
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, nums[N];

ll solve() {
    set<ll> set;
    ll lo = 0, hi = 1e9;
    for(int i = n; i >= 1; i--) {
        ll a = nums[i];
        auto it = set.upper_bound(a);
        if(it != set.end()) {
            ll b = *it, x = (b + a) / 2;
            hi = min(hi, x);
        }
        it = set.lower_bound(a);
        if(!set.empty() && it != set.begin()) {
            ll b = *(--it), x = (a + b + 1) / 2;
            lo = max(lo, x);
        }
        if(lo > hi) return -1;
        set.insert(a);
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};