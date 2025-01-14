/**
 * @Time : 2025/1/13-11:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2408C 1200 位运算 贪心 暴力枚举
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n;
string s;

bool more(int i, int j1, int j2) {
    for( ; i < n; i++, j1++, j2++) {
        int n1 = s[i] - '0', n2 = s[j1] - '0', n3 = s[j2] - '0';
        if((n1 ^ n2) > (n1 ^ n3)) return true;
        else if((n1 ^ n2) < (n1 ^ n3)) return false;
    }
    return false;
}

void solve() {
    int i = 1;
    while (i < n && s[i] == '1') i++;
    if(i == n) { // s本身全是1的情况
        cout << 1 << " " << n - 1 << " " << "1 1\n";
        return;
    }
    int len = n - i, idx = -1;
    for(int j = 1; j + len - 1 < n; j++) {
        if(s[j] == '1' && (idx == -1 || more(i, j, idx)))
            idx = j;
    }
    cout << 1 << " " << n - 1 << " " << idx << " " << idx + len - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> s;
        s = '.' + s;
        n = s.size();
        solve();
    }
};