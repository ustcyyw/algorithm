/**
 * @Time : 2024/3/21-9:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 下标从1开始计算 那就是取奇数下标的最大和
 * 如果选取的翻转区间长度为奇数 那么翻转后下标的奇偶性不变
 * 因此要和不翻转有区别 就得翻转偶数长度的区间 该区间上下标奇偶性变化
 * 假设翻转的区间是nums[i, j]，这种情况下的和为 odd[i-1] + odd[n] - odd[j] + even[j] - even[i-1]
 * 枚举j，那么odd[n] - odd[j] + even[j]为一个确定值，找最大的odd[i-1] - even[i-1]即可
 * 因此在枚举过程中也不断记录 odd[i-1] - even[i-1] 的最大值即可。
 * 并且要分下标的奇偶性分开记录 因为要保证翻转区间长度为偶数
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, nums[N], odd[N] = {0}, even[N] = {0};

void solve() {
    ll ans = odd[n], oi = 0, ei = 0;
    for (int j = 1; j <= n; j++) {
        ll temp = odd[n] - odd[j] + even[j], cur = odd[j] - even[j];
        // j为奇数，要求i为偶数，那么nums[i,j]长才为偶数，此时i-1为奇数
        if (j % 2 == 1) temp += oi, oi = max(oi, cur);
        else temp += ei, ei = max(ei, cur);
        ans = max(ans, temp);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> nums[i];
            odd[i] = odd[i - 1], even[i] = even[i - 1];
            if (i % 2 == 1) odd[i] += nums[i];
            else even[i] += nums[i];
        }
        solve();
    }
};