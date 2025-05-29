/**
 * @Time : 2025/5/22-8:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1073C 1800 枚举 二分答案 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
int T, n, x, y, ls[N], rs[N], us[N], ds[N];
string s;

bool check_zero() {
    int dx = 0, dy = 0;
    for(char c : s) {
        if(c == 'L') dx--;
        else if(c == 'R') dx++;
        else if(c == 'U') dy++;
        else dy--;
    }
    return dx == x && dy == y;
}

void init(int* sum, char c) {
    for(int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + (s[i] == c);
    }
}

bool check(int l, int r) {
    int cl = ls[n] - (ls[r] - ls[l - 1]);
    int cr = rs[n] - (rs[r] - rs[l - 1]);
    int cu = us[n] - (us[r] - us[l - 1]);
    int cd = ds[n] - (ds[r] - ds[l - 1]);
    int dx = cr - cl, dy = cu - cd;
    dx = abs(x - dx), dy = abs(y - dy);
    return dx + dy <= r - l + 1;
}

int solve() {
    int len = abs(x) + abs(y);
    if(len > n || (n - len) % 2 == 1) return -1;
    if(check_zero()) return 0;
    s = '.' + s;
    init(ls, 'L'), init(rs, 'R'), init(us, 'U'), init(ds, 'D');
    int ans = INT_MAX;
    for(int i = 1; i <= n; i++) {
        int lo = i, hi = n + 1;
        while(lo < hi) {
            int mid = (lo + hi) >> 1;
            if(check(i, mid)) hi = mid;
            else lo = mid + 1;
        }
        if(lo != n + 1) ans = min(ans, lo - i + 1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    cin >> T;
    cin >> n >> s >> x >> y;
    cout << solve();
}