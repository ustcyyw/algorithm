/**
 * @Time : 2025/3/30-11:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF962B 1300 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, M = 30;
int n, a, b;
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a >> b >> s;
    int cnt = 0;
    for(int i = 0; i < s.size() && a + b > 0; i++) {
        if(s[i] == '*') continue;
        if(a >= b) {
            if(i == 0 || s[i - 1] != 'A') cnt++, s[i] = 'A';
            else if(b > 0) cnt++, s[i] = 'B';
        } else {
            if(i == 0 || s[i - 1] != 'B') cnt++, s[i] = 'B';
            else if(a > 0) cnt++, s[i] = 'A';
        }
        if(s[i] == 'A') a--;
        else if(s[i] == 'B') b--;
    }
    cout << cnt;
}