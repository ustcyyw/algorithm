/**
 * @Time : 2024/4/10-11:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 枚举边 边的平行判定可以使用向量同向来判断
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll N = 2005, T = 2e9 + 1;
int n;
vector<vector<int>> pos;
void solve() {
    sort(pos.begin(), pos.end()); // 保证了dx >= 0。并且dx = 0时，dy >= 0
    unordered_map<ll, int> map;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int x1 = pos[i][0], y1 = pos[i][1];
        for(int j = i + 1; j < n; j++) {
            int x2 = pos[j][0], y2 = pos[j][1];
            ll dx = x2 - x1, dy = y2 - y1;
            ll key = dx * T + dy;
            ans += map[key];
            map[key]++;
        }
    }
    cout << (ans / 2);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, x, y; i <= n; i++) {
        cin >> x >> y;
        pos.push_back({x, y});
    }
    solve();
};