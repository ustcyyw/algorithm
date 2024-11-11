/**
 * @Time : 2023/12/12-9:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
int T, n, sum[N] = {0}; // sum 是1的前缀和
string s;

int zero(int l, int r) {
    return r - l + 1 - (sum[r + 1] - sum[l]);
}

int one(int l, int r) {
    return sum[l] + sum[n] - sum[r + 1];
}

void solve() {
    n = s.size();
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + s[i - 1] - '0';
    int res = INT_MAX;
    for(int l = 0, r = 0; r < n; ) {
        while(r < n && zero(l, r) <= one(l, r)) r++;
        res = min(res, max(zero(l, r - 1), one(l, r - 1)));
        l++;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        solve();
    }
};
