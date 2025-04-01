/**
 * @Time : 2025/3/31-9:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF976C 1500 贪心 排序
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
ll n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    vector<vector<int>> ranges;
    for(int i = 1, l, r; i <= n; i++) {
        cin >> l >> r;
        ranges.push_back({l, r, i});
    }
    sort(ranges.begin(), ranges.end(), [](auto& a, auto& b) -> int {
        if(a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });
    for(int i = n - 2, j = n - 1; i >= 0; i--) {
        if(ranges[i][1] >= ranges[j][1]) {
            cout << ranges[j][2] << " " << ranges[i][2];
            return 0;
        } else j = i;
    }
    cout << -1 << " " << -1;
}