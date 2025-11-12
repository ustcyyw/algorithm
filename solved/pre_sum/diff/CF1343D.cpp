/**
 * @Time : 2024/6/25-2:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1343D 差分 暴力枚举
 */
 /*
  * 根据两个数的情况 确定将这两个数改动到[2, 2 * k]上的值需要几次操作
  * 其实是分为4中情况 改小需要2次操作或者1次操作、改大需要2次操作或者1次操作
  * 可以用差分的思路来记录修改次数
  *
  * 枚举两个数之和
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, k, nums[N];
vector<int> arr;

void solve() {
    for(int i = 1, j = n; i <= n / 2; i++, j--) {
        int a = nums[i], b = nums[j];
        int t1 = min(a, b) + 1, t2 = max(a, b) + k;
        arr[2] += 2, arr[t1] -= 2;
        arr[t1]++, arr[a + b]--;
        arr[a + b + 1]++, arr[t2 + 1]--;
        arr[t2 + 1] += 2, arr[2 * k + 1] -= 2;
    }
    int ans = INT_MAX;
    for(int i = 2, sum = 0; i <= 2 * k; i++) {
        sum += arr[i];
        ans = min(ans, sum);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        arr.assign(2 * k + 1, 0);
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};