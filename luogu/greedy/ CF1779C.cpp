/**
 * @Time : 2024/1/31-10:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 有点反悔贪心的意思
 */
/*
 * 在m的右边
 * sum[m + 1] = nums[m + 1] + sum[m]
 * sum[m + 1] >= sum[m] 就要求 nums[m + 1] >= 0
 *
 * sum[m + 2] = nums[m + 1] + nums[m + 2] + sum[m]
 * nums[m + 1] + nums[m + 2] >= 0
 * ...
 * nums[m + 1] + ... + nums[n] >= 0
 * 整个累加数必须 >= 0
 * 遇到累加为负 就必须选一个数取反 选一个之前最小的负数取反（这样操作才尽可能少）
 *
 * 在m的左边
 * sum[m - 1] + nums[m] = sum[m]
 * nums[m] <= 0
 *
 * sum[m - 2] + nums[m - 1] + nums[m] = sum[m]
 * nums[m - 1] + nums[m] <= 0
 * ...
 * sum[1] + (nums[2] + .. + nums[m]) = sum[m]
 * nums[2] + .. + nums[m] <= 0
 * 整个累加数必须 <= 0
 * 遇到累加为负 就必须选一个数取反 选一个之前最小的负数取反
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
int T, n, m, nums[N];

void change_right(int& cnt, int start, int sign) {
    if(nums[start] < 0) cnt++;
    long long sum = abs(nums[start]);
    priority_queue<int,vector<int>, greater<>> pq;
    for(int i = start + sign; i > 1 && i <= n; i += sign) {
        if(nums[i] < 0) pq.push(nums[i]);
        sum += nums[i];
        if(sum < 0) {
            sum -= (long long)2 * pq.top();
            cnt++, pq.pop();
        }
    }
}

void change_left(int& cnt, int start, int sign) {
    if(nums[start] > 0) cnt++;
    long long sum = -abs(nums[start]);
    priority_queue<int> pq;
    for(int i = start + sign; i > 1 && i <= n; i += sign) {
        if(nums[i] > 0) pq.push(nums[i]);
        sum += nums[i];
        if(sum > 0) {
            sum -= (long long)2 * pq.top();
            cnt++, pq.pop();
        }
    }
}

int solve() {
    int cnt = 0;
    change_right(cnt, m + 1, 1);
    if(m > 1) change_left(cnt, m, -1); // 注意m=1的话 不存在m的左边
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
};