/**
 * @Time : 2024/5/8-11:01 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要求区间和相同 且求最大不交叉区间数量
 * 那么应该先把和相同的区间归类到一组 在每一组中找最大不交叉区间数量
 * 问题转化为 P1803线段覆盖
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1505, T = 1e9 + 1;
int n, nums[N];
unordered_map<int, vector<vector<int>>> arrs;

vector<vector<int>> max_group(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    vector<vector<int>> res;
    for(auto& range : arr) {
        if(res.empty() || res.back()[1] < range[0])
            res.push_back(range);
    }
    return res;
}

void solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = i, sum = 0; j <= n; j++) {
            sum += nums[j];
            arrs[sum].push_back({i, j});
        }
    }
    vector<vector<int>> res;
    for(auto& p : arrs) {
        vector<vector<int>> temp = max_group(p.second);
        if(temp.size() > res.size())
            swap(temp, res);
    }
    cout << res.size() << "\n";
    for(auto& p : res)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};