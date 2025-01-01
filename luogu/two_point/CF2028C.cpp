/**
 * @Time : 2024/12/31-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2028C 1600 双指针 前后缀分解 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, m, low, nums[N], sum[N];

ll solve() {
    map<int, int> pre;
    pre[0] = 0;
    for(int i = 1, j, cnt = 1; i <= n; i = j) {
        ll temp = 0;
        j = i;
        while(j <= n && temp < low)
            temp += nums[j++];
        if(temp >= low) pre[cnt++] = j - 1;
    }
    if(!pre.count(m)) return -1;
    ll ans = sum[n] - sum[pre[m]];
    for(int i = n, j, cnt = 1; i >= 1; i = j) {
        ll temp = 0;
        j = i;
        while(j >= 1 && temp < low)
            temp += nums[j--];
        if(temp >= low) ans = max(ans, sum[j] - sum[pre[m - cnt]]);
        cnt++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> low;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
        }
        cout << solve() << "\n";
    }
};