/**
 * @Time : 2025/2/25-9:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF803B 1200 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 400;
int n, k, nums[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<int> ans(n + 1, INT_MAX);
    for(int i = 1, pre = -1; i <= n; i++) {
        cin >> nums[i];
        if(nums[i] == 0) pre = i;
        if(pre != -1) ans[i] = i - pre;
    }
    for(int i = n, nxt = -1; i >= 1; i--) {
        if(nums[i] == 0) nxt = i;
        if(nxt != -1) ans[i] = min(ans[i], nxt - i);
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}