/**
 * @Time : 2024/6/15-10:38 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1272B
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n;
string s;

void append(string& t, int cnt, char c) {
    while(cnt-- > 0)
        t.push_back(c);
}

void solve() {
    int cl = 0, cr = 0, cu = 0, cd = 0;
    for(char c : s) {
        if(c == 'L') cl++;
        else if(c == 'R') cr++;
        else if(c == 'U') cu++;
        else cd++;
    }
    int m1 = min(cl, cr), m2 = min(cu, cd), ans = 0;
    if(m1 == 0) m2 = min(m2, 1);
    if(m2 == 0) m1 = min(m1, 1);
    ans = cl - m1 + cr - m1 + cu - m2 + cd - m2;
    cout << s.size() - ans << "\n";
    string t;
    append(t, m1, 'L'), append(t, m2, 'U'), append(t, m1, 'R'), append(t, m2, 'D');
    cout << t << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        solve();
    }
};