/**
 * @Time : 2025/3/5-9:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF846B 1800 暴力枚举 贪心
 */
 /*
  * 暴力枚举有多少个任务是完全完成的
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, P = 13331;
ll n, k, m, nums[N];

void solve() {
    ll ans = 0, sum = accumulate(nums, nums + k + 1, 0ll);
    for(int i = 0; i <= n && i * sum <= m; i++) {
        ll left = m - i * sum, temp = (k + 1) * i;
        for(int j = 1; j <= k; j++) {
            if(left >= nums[j] * (n - i)) {
                left -= nums[j] * (n - i);
                temp += n - i;
            } else {
                temp += left / nums[j];
                break;
            }
        }
        ans = max(ans, temp);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> m;
    for(int i = 1; i <= k; i++)
        cin >> nums[i];
    sort(nums + 1, nums + k + 1);
    solve();
}