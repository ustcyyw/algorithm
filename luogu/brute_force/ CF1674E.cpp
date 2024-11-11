/**
 * @Time : 2024/8/1-10:27 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1674E 贪心 暴力枚举
 */
/*
 * a b c d
如果要打破a d 肯定是直接作用在a和d上 相当于找最小的两个数
如果要打破ab、bc、cd就是枚举位置，算如何最快捆绑地打破
如果要打破ac、bd 也是枚举位置 看左右两边如何被打破
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, nums[N];

int cal1() {
    int n1 = INT_MAX, n2 = INT_MAX;
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        if(num < n1) n2 = n1, n1 = num;
        else if(num < n2) n2 = num;
    }
    return (n1 + 1) / 2 + (n2 + 1) / 2;
}

int cal2() {
    int ans = INT_MAX;
    for(int i = 2; i < n; i++) {
        // 先通过两边-1的操作，将一边变为0，然后剩下那边直接操作
        int t = min(nums[i - 1], nums[i + 1]);
        int val = max(nums[i - 1], nums[i + 1]) - t;
        ans = min(ans, t + (val + 1) / 2);
    }
    return ans;
}

int f(int n1, int n2) {
    if(n1 < n2) swap(n1, n2);
    int t1 = (n1 + 1) / 2;
    if(t1 >= n2) return t1; // 意味着每次攻击较高的墙 都会顺带将矮墙击破
    t1 = n1 - n2; // 现在t1表示 先攻击高墙t1次 会使得两个墙一样高
    n1 -= 2 * t1;
    return t1 + 2 * (n1 / 3) + n1 % 3;
}

int cal3() {
    int ans = INT_MAX;
    for(int i = 1; i < n; i++) {
        ans = min(ans, f(nums[i], nums[i + 1]));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    cout << min({cal1(), cal2(), cal3()}) << endl;
};