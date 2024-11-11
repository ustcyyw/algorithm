/**
 * @Time : 2024/4/26-4:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1102D
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e4 + 5, mod = 998244353;
int n;
string s;

void solve() {
    int cnt[3] = {0, 0, 0};
    for(char c : s)
        cnt[c - '0']++;
    int m = n / 3, zero = cnt[0], one = cnt[1], two = cnt[2];
    for(int i = 0; i < n && zero < m; i++) {
        if(s[i] == '1' && one > m)
            s[i] = '0', one--, zero++;
        if(s[i] == '2' && two > m)
            s[i] = '0', two--, zero++;
    }
    // 对于2来说 如果2不足 应该从后面开始换
    for(int i = n - 1; i >= 0 && two < m; i--) {
        if(s[i] == '0' && zero > m)
            s[i] = '2', zero--, two++;
        if(s[i] == '1' && one > m)
            s[i] = '2', one--, two++;
    }
    // 保证了0或者2要么已经满足数目要求 要么就是多了 从后面将0换1 从前面将2换1
    for(int i = 0; i < n && one < m; i++) {
        if(s[i] == '2' && two > m)
            s[i] = '1', two--, one++;
    }
    for(int i = n - 1; i >= 0 && one < m; i--) {
        if(s[i] == '0' && zero > m)
            s[i] = '1', zero--, one++;
    }
    cout << s;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    solve();
};