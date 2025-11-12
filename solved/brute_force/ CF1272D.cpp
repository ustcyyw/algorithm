/**
 * @Time : 2024/6/15-10:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1272D
 */
 /*
  * 暴力枚举前后两个相邻的上升子数组 看看怎么删除交界处元素 让两个子数组拼起来
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, nums[N], b[N];

void solve() {
    int ans = 1;
    for(int i = 1, j; i <= n; ) {
        j = i + 1;
        while(j <= n && nums[j] > nums[j - 1]) j++;
        b[i] = j - 1;
        ans = max(ans, j - i);
        i = j;
    }
    for(int i = 1, j, k; i <= n; i = b[i] + 1) {
        j = b[i], k = j + 1;
        if((j > i && nums[j - 1] < nums[k]) || (b[k] > k && nums[j] < nums[k + 1]))
            ans = max(ans, j - i + b[k] - k + 1);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    solve();
};