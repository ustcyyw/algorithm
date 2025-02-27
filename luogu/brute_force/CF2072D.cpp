/**
 * @Time : 2025/2/26-10:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2072D 暴力枚举
 */
 /*
  * 暴力枚举区间
  * 区间外的数与区间内的数 相对位置关系不变 不影响逆序对数量
  * 区间内除了al与其它数相对位置变化了，其它对也不变 也不影响逆序对数量
  * 因此只用关注al和区间内其它数的情况即可
  * 在区间中 比al小的数 操作前是逆序对；比al大的数 操作后是逆序对
  * 所以可以计算逆序对的变化量 找变化最小的区间
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e3 + 5, mod = 1e9 + 7;
ll T, n, nums[N];

void solve() {
    int cnt = 0, l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        int less = 0, more = 0;
        for(int j = i + 1; j <= n; j++) {
            if(nums[j] > nums[i]) more++;
            if(nums[j] < nums[i]) less++;
            if(more - less< cnt)
                cnt = more - less, l = i, r = j;
        }
    }
    cout << l << " " << r << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
}