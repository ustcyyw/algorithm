/**
 * @Time : 2024/4/29-2:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1108E1 前后缀分解+差分
 */
/*
 * 可以枚举最大值的下标 在确定最大值下标i的情况下
 * 任何包括i的区间操作都不应该 因为
 * 如果能取得答案的最小值也在这个区间内 那么最大值和最小值的差值不变
 * 如果能取得答案的最小值不在这个区间内 那么反而导致答案减小了
 * 那么其它区间操作肯定要都执行 因为最大值固定了 那么只要不影响最大值 让其它所有数变小有利
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305, mod = 998244353;
int n, m, nums[N], diff[N], suf[N];
vector<vector<int>> range;

void solve() {
    sort(range.begin(), range.end());
    // 先计算后缀
    fill(suf, suf + n + 1, INT_MAX);
    for(int i = n, j = m - 1; i >= 1; i--) {
        while(j >= 0 && range[j][0] > i) {
            int l = range[j][0], r = range[j][1];
            diff[l - 1]++, diff[r]--;
            j--;
        }
        for(int k = n, sum = 0; k > i; k--) {
            sum += diff[k];
            suf[i] = min(suf[i], nums[k] + sum);
        }
    }
    // 计算前缀的同时求出答案
    int ans = 0, mi = 1;
    sort(range.begin(), range.end(), [](auto &a, auto &b) -> bool {
        return a[1] < b[1];
    });
    memset(diff, 0, sizeof(diff));
    for(int i = 1, j = 0; i <= n; i++) {
        while(j < m && range[j][1] < i) {
            int l = range[j][0], r = range[j][1];
            diff[l]--, diff[r + 1]++;
            j++;
        }
        int pre = 2e7;
        for(int k = 1, sum = 0; k < i; k++) {
            sum += diff[k];
            pre = min(pre, nums[k] + sum);
        }
        int temp = nums[i] - min(pre, suf[i]);
        if(temp > ans) ans = temp, mi = i;
    }
    cout << ans << "\n";
    vector<int> pick;
    for(auto& arr : range) {
        if(arr[0] > mi || arr[1] < mi) pick.push_back(arr[2]);
    }
    cout << pick.size() << "\n";
    for(int num : pick)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    for(int i = 1, l, r; i <= m; i++) {
        cin >> l >> r;
        range.push_back({l, r, i});
    }
    solve();
};