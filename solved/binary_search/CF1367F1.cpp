/**
 * @Time : 2024/6/30-7:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1367F1 枚举 + 二分
 */
/*
  * 枚举移动到头部的操作次数lower 并且移动的顺序得先移动lower，再移动lower - 1...
  * 同时再lower确定的情况下 计算最少使用多次移动到尾部到操作次数higher
  * 可以使用二分 二分higher 将已经移动的较大数和较小数忽略 看剩下的数是否已经是递增序列
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e3 + 5;
typedef long long ll;
int T, n, nums[N];
map<int, int> mp;

bool check(int lower, int higher) {
    for(int i = 1, pre = -1; i <= n; i++) {
        int num = nums[i];
        if(num > lower && num < higher) {
            if(num < pre) return false;
            pre = num;
        }
    }
    return true;
}

int cal(int lower) {
    int lo = 0, hi = n - lower;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(lower, n - mid + 1)) hi = mid;
        else lo = mid + 1;
    }
    return lo + lower;
}

void solve() {
    int ans = n;
    for(int i = 0; i < n; i++) {
        ans = min(ans, cal(i));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        mp = {};
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            mp[nums[i]] = i;
        }
        int i = 0;
        for(auto& p : mp)
            nums[p.second] = ++i;
        solve();
    }
};