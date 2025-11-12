/**
 * @Time : 2024/1/22-12:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> tower;

int search(int index) {
    int val = tower[index][0] - tower[index][1];
    int lo = 0, hi = index - 1;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(tower[mid][0] >= val) hi = mid - 1;
        else lo = mid;
    }
    return lo;
}

void solve() {
    // 预处理 如果当前塔激活 会摧毁多少数量的塔
    vector<int> cnt(n + 1, 0);
    for(int i = 1; i <= n; i++) {
        int j = search(i);
        cnt[i] = cnt[j] + i - (j + 1);
    }
    int res = INT_MAX;
    for(int i = n; i > 0; i--)
        res = min(res, cnt[i] + n - i);
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    tower.clear();
    tower.push_back({-1, -1}); // 哨兵
    cin >> n;
    for(int i = 0, a, b; i < n; i++) {
        cin >> a >> b;
        tower.push_back({a, b});
    }
    sort(tower.begin(), tower.end());
    solve();
}