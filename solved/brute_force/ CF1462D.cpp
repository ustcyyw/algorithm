/**
 * @Time : 2024/7/7-4:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1462D 暴力枚举 双指针
 */
 /*
  * 一次操作减少一个数 并且只能合并到相临的数
  * 要让最终所有数相等，等价于可以分成多少个相等的子数组和
  * 值相等的子数组越多 操作次数越少。
  * 因此可以枚举第一个子数组的右边界 这样就确定了子数组的和应该是多少
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, nums[N];

int cal(int sum, int start) {
    int cnt = 0;
    for(int i = start, j, temp; i <= n; ) {
        j = i, temp = 0;
        while(j <= n && temp < sum)
            temp += nums[j++];
        if(temp != sum) return -1;
        i = j, cnt++;
    }
    return cnt;
}

void solve() {
    int ans = 1;
    for(int i = 1, sum = 0; i <= n; i++) {
        sum += nums[i];
        int t = cal(sum, i + 1);
        if(t != -1) ans = max(ans, 1 + t);
    }
    cout << n - ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};