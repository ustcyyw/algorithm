/**
 * @Time : 2024/9/24-3:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1907F
 */
/*
  * 降序通过平移动操作后 在开头仍然是降序
  * 如果是升序-降序的组合 将降序序列一部分移动到前面后 先降序 再升序 没有变成单调的
  * 必须是 降序-降序 或者 升序-升序 这样的结构才能完成排列
  * 所以先判断数组的单调性构成 在单调性确定的基础上
  * 1. 降序-降序组合 要求第二部分降序的最小值（最后一个值） >= 第一部分最大值（第一个值）
  * 2. 升序-升序组合 要求第二部分最后一个值 <= 第一部分第一个值
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n;
vector<int> nums;

// 找到以lo开头的升序序列或者降序序列末尾索引 flag = 1 找升序序列， flag = -1 找降序序列
int find(int lo, int flag) {
    for(; lo + 1 < n; lo++) {
        if(flag * nums[lo] > flag * nums[lo + 1])
            break;
    }
    return lo;
}

int cal(int i1, int i2, int j1, int j2) {
    // 升序-升序组合
    int t1 = INT_MAX;
    if(i2 == n - 1 && nums[0] >= nums[n - 1]) // i2 != n - 1 意味着数组不是升序-升序组合
        t1 = n - 1 - (i1 + 1) + 1;
    int t2 = INT_MAX;
    if(j2 == n - 1 && nums[n - 1] >= nums[0])
        t2 = n - 1 - (j1 + 1) + 1 + 1; // 多加了一个1表示得到完整降序序列后 需要翻转一次
    return min(t1, t2);
}

int cal() {
    int i1 = find(0, 1), i2 = find(i1 + 1, 1);
    if(i1 == n - 1) return 0;
    int j1 = find(0, -1), j2 = find(j1 + 1, -1);
    if(j1 == n - 1) return 1;
    return cal(i1, i2, j1, j2);
}

int solve() {
    // 先不使用翻转
    int t1 = cal();
    reverse(nums.begin(), nums.end());
    int t2 = cal();
    if(t2 != INT_MAX) t2++; // 一开始将数组翻转用的1此操作
    return min(t1, t2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        nums.assign(n, 0);
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        int ans = solve();
        cout << (ans == INT_MAX ? -1 : ans) << "\n";
    }
};