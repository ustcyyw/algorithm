/**
 * @Time : 2024/6/15-10:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1272C 双指针
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, k, a[26];
char c;
string s;

void solve() {
    ll ans = 0;
    for(int i = 0, j; i < n; ) {
        while(a[s[i] - 'a'] == 0) i++;
        j = i;
        while(j < n && a[s[j] - 'a']) j++;
        ll len = j - i;
        ans += (len + 1) * len / 2;
        i = j;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    cin >> s;
    for(int i = 1; i <= k; i++) {
        cin >> c;
        a[c - 'a'] = 1;
    }
    solve();
};