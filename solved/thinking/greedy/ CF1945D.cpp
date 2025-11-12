/**
 * @Time : 2024/3/20-9:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 假设要到达第i个位置
 * 并且在过程中从后往前交换了 j1,j2...jx 这些位置
 * 那么总的花费是 a[j1] + sum_b[j1-1, j2+1] + a[j2] + sum[j2-1,j3+1] + ... + a[jx]
 * 求和的下标是连续的 要交换的j是自己选的
 * 那么在a[j] < b[j]的地方就使用交换操作 能让这个区间求和最小。
 * 从后往前进行计算，当最后一个交换的位置i 满足i <= m && i >= 1时，是一个可行的方案
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, m, a[N], b[N], sum[N];

ll solve() {
    sum[n + 1] = 0;
    ll ans = LONG_LONG_MAX;
    for(int i = n; i >= 0; i--) {
        sum[i] = sum[i + 1] + min(a[i], b[i]);
        if(i <= m && i >= 1)
            ans = min(ans, sum[i + 1] + a[i]);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        cout << solve() << "\n";
    }
};