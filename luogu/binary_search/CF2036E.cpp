/**
 * @Time : 2024/11/21-11:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2036E 二分 1600
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 1000000;
int T, n, k, q, r, c, m;
char ope;
vector<vector<int>> area;
// 在区间[lb,rb]上找到值大于c的边界
int low_bound(int lb, int rb) {
    if(area[rb][r] <= c) return -1;
    int lo = lb, hi = rb;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(area[mid][r] <= c) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
// 在区间[lb,rb]上找到值小于c的边界
int up_bound(int lb, int rb) {
    if(area[lb][r] >= c) return -1;
    int lo = lb, hi = rb;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(area[mid][r] >= c) hi = mid - 1;
        else lo = mid;
    }
    return lo;
}

int check() {
    cin >> m;
    int lo = 1, hi = n;
    for(int i = 1; i <= m; i++) {
        cin >> r >> ope >> c;
        if(lo == -1) continue;
        int t = ope == '>' ? low_bound(lo, hi) : up_bound(lo, hi);
        if(t == -1) lo = -1;
        if(ope == '>') lo = t;
        else hi = t;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> k >> q;
        area.assign(n + 1, vector(k + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= k; j++) {
                cin >> area[i][j];
                area[i][j] |= area[i - 1][j];
            }
        }
        for(int i = 1; i <= q; i++) {
            cout << check() << "\n";
        }
    }
};