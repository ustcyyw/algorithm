/**
 * @Time : 2024/6/21-4:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1328C 贪心
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, k;
string s;

void solve() {
    string a, b;
    for(int i = 0, flag = 0; i < n; i++) {
        if(flag) {
            a.push_back('0'), b.push_back(s[i]);
            continue;
        }
        if(s[i] == '2') a.push_back('1'), b.push_back('1');
        else if(s[i] == '0') a.push_back('0'), b.push_back('0');
        else {
            flag = 1;
            a.push_back('1'), b.push_back('0');
        }
    }
    cout << a << "\n" << b << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        solve();
    }
};