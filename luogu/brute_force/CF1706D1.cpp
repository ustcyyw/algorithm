/**
 * @Time : 2024/6/4-10:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1706D1 暴力枚举
 */
 /*
  * 暴力枚举 ai/pi的最大值val 保证所有ai/pi <= val
  * 然后找一个pi使得 ai/pi 最接近val
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 3005, MV = 1e9;
typedef long long ll;
int T, n, k, nums[N];

int cal(int num, int val) {
    int pi = num / val;
    int p1 = min(pi + 1, k), p2 = min(max(1, pi), k);
    int v1 = num / p1, v2 = num / p2;
    if(v1 > val) v1 = -1;
    if(v2 > val) v2 = -1;
    return max(v1, v2);
}

int min_diff(int val) {
    int v1 = INT_MAX, v2 = INT_MIN;
    for(int i = 1; i <= n; i++) {
        int t = cal(nums[i], val);
        if(t == -1) return INT_MAX;
        v1 = min(v1, t), v2 = max(v2, t);
    }
    return v2 - v1;
}

void solve() {
    int ans = INT_MAX;
    for(int val = 1; val <= 3000; val++) {
        ans = min(ans, min_diff(val));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};