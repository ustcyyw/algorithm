/**
 * @Time : 2025/3/19-5:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954B 1400 贪心 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e4 + 15, mod = 1e9 + 7;
ll T, n;
string s;

int solve() {
    for(int i = n - 1; i >= 0; i--) {
        if((i + 1) % 2 == 0) {
            int len = (i + 1) / 2;
            if(s.substr(0, len) == s.substr(len, len))
                return len + 1 + n - 1 - (i + 1) + 1;
        }
    }
    return n;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    cout << solve();
}