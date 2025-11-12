/**
 * @Time : 2025/3/2-10:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF837B 1600 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
int T, n, m;
string s[N];

char check(int i1, int i2, int j1, int j2) {
    char c = s[i1][j1];
    for(int i = i1; i <= i2; i++) {
        for(int j = j1; j <= j2; j++) {
            if(s[i][j] != c) return '0';
        }
    }
    return c;
}

bool solve() {
    if(n % 3 == 0) {
        int d = n / 3;
        char c1 = check(0, d - 1, 0, m - 1);
        char c2 = check(d, 2 * d - 1, 0, m - 1);
        char c3 = check(2 * d, n - 1, 0, m - 1);
        if(c1 != '0' && c2 != '0' && c3 != '0' && c1 != c2 && c2 != c3 && c1 != c3)
            return true;
    }
    if(m % 3 == 0) {
        int d = m / 3;
        char c1 = check(0, n - 1, 0, d - 1);
        char c2 = check(0, n - 1, d, 2 * d - 1);
        char c3 = check(0, n - 1, 2 * d, m - 1);
        if(c1 != '0' && c2 != '0' && c3 != '0' && c1 != c2 && c2 != c3 && c1 != c3)
            return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> s[i];
    cout << (solve() ? "YES" : "NO");
}