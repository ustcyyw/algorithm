/**
 * @Time : 2024/8/7-3:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1729D 贪心
 */
/*
 * x是花费 y是预算 最大多少组 y > x，计算yi - xi
 * 如果一个赊欠的需要两个盈余的来组合 还不如让两个盈余的自己走
 * 所以一个赊欠的找不到单一盈余的搭配 直接跳过即可
 * 这样搭配完之后 剩下所有盈余的人 还可以各自两两配对
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 9;
typedef long long ll;
int T, n, x[N], y[N];

void solve() {
    vector<int> neg, pos;
    for(int i = 1; i <= n; i++) {
        int diff = y[i] - x[i];
        if(diff >= 0) pos.push_back(diff);
        else neg.push_back(diff);
    }
    sort(neg.begin(), neg.end()), sort(pos.begin(), pos.end());
    int cnt = 0, m1 = neg.size(), m2 = pos.size();
    for(int i = 0, j = m2 - 1; i < m1 && j >= 0; i++, j--) {
        while(i < m1 && neg[i] + pos[j] < 0) i++;
        if(i != m1) cnt++;
    }
    cout << cnt + (m2 - cnt) / 2  << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> x[i];
        for(int i = 1; i <= n; i++)
            cin >> y[i];
        solve();
    }
};