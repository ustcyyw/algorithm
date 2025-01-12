/**
 * @Time : 2025/1/11-3:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2051D 1200 排序 双指针
 */
 /*
  * b1 <= sum - x - a
  * b2 >= sum - y - a
  *
  * 随着a增大 b1减小 b2也可以减小
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, x, y, nums[N];

void solve() {
    ll sum = accumulate(nums + 1, nums + n + 1, 0ll), ans = 0;
    for(int i = 1, j1 = n, j2 = n; i <= j1; i++) {
        while(j1 >= 1 && nums[j1] > sum - x - nums[i])
            j1--;
        while(j2 >= 1 && nums[j2] >= sum - y - nums[i])
            j2--;
        if(j1 >= i) ans += j1 - max(j2 + 1, i + 1) + 1;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n >> x >> y;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sort(nums, nums + n + 1);
        solve();
    }
};