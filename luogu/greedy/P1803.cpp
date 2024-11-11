/**
 * @Time : 2024/5/8-10:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P1803 贪心
 */
/*
 * dp[i]: 以第i个区间为结尾的最大区间数量
 * 前置区间 [lj,rj] 当前区间[li, ri]
 * 对于所有 rj < li 都可以当做当前区间的前置区间
 * dp[i] = max{dp[j] + 1, for rj < li}
 * 对于dp[j]值相同的多个j 保留rj最小的一个即可 这样更利于后面的区间可以选择
 *
 * 将区间按右端点排序后
 * 只要有rj < li就选择当前区间 就保留了最大区间值下r最小的区间
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1505, T = 1e9 + 1;
int n;
vector<vector<int>> arr;

void solve() {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    vector<vector<int>> res;
    for(auto& range : arr) {
        if(res.empty() || res.back()[1] <= range[0])
            res.push_back(range);
    }
    cout << res.size();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        arr.push_back({l, r});
    }
    solve();
};