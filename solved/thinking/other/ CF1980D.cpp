/**
 * @Time : 2024/12/3-2:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1980D 1400 前后缀分解
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, nums[N], g[N];

bool solve() {
    if(n == 3) return true;
    for(int i = 1; i < n; i++)
        g[i] = gcd(nums[i], nums[i + 1]);
    g[n] = INT_MAX;
    vector<bool> pre(n + 1, false), suf(n + 1, false);
    pre[0] = pre[1] = suf[n - 1] = suf[n] = true;
    for(int i = 2; i < n; i++) {
        if(g[i] >= g[i - 1]) pre[i] = true;
        else break;
    }
    for(int i = n - 2; i >= 1; i--) {
        if(g[i] <= g[i + 1]) suf[i] = true;
        else break;
    }
    if(pre[n - 2] || suf[2]) return true;
    for(int i = 2; i <= n - 1; i++) {
        int temp = gcd(nums[i - 1], nums[i + 1]);
        if(pre[i - 2] && suf[i + 1] && temp >= g[i - 2] && temp <= g[i + 1])
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    };
};