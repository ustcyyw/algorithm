/**
 * @Time : 2024/5/14-11:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1165C 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305, mod = 998244353;
int T, n;
string s;

void solve() {
    int cnt = 0;
    for(int i = 1; i < n; i++) {
        if(s[i] == s[i + 1] && (i - cnt) % 2 == 1) {
            s[i] = '.';
            cnt++;
        }
    }
    if((n - cnt) % 2 == 1) { // 保持偶数长度
        cnt++;
        s.back() = '.';
    }
    cout << cnt << "\n";
    for(char c : s)
        if(c != '.') cout << c;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    cin >> s;
    s = '.' + s;
    solve();
};