/**
 * @Time : 2025/2/13-12:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : ABC215F 1853 二分答案 双指针
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n;
vector<vector<int>> points;

bool check(int dis) {
    for(int i = 0, j = 0, minV = INT_MAX, maxV = INT_MIN; i < n; i++) {
        while(j < n && points[i][0] - points[j][0] >= dis) {
            minV = min(minV, points[j][1]), maxV = max(maxV, points[j][1]);
            j++;
        }
        if(minV != INT_MAX) {
            int d = max(points[i][1] - minV, maxV - points[i][1]);
            if(d >= dis) return true;
        }
    }
    return false;
}

void solve() {
    int lo = 0, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1, x, y; i <= n; i++) {
            cin >> x >> y;
            points.push_back({x, y});
        }
        sort(points.begin(), points.end());
        solve();
    }
};