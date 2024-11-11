/**
 * @Time : 2024/7/4-7:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1409D 贪心 数学
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, s, sum[25];
string t;

ll solve() {
    int m = t.size();
    for(int i = 1; i < m; i++)
        sum[i] = sum[i - 1] + t[i] - '0';
    if(sum[m - 1] <= s) return 0;
    for(ll i = m - 1, base = 10; i >= 0; i--, base *= 10) {
        if(sum[i - 1] + 1 <= s) {
            ll num = stoll(t.substr(i));
            return base - num;
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> t >> s;
        t = '.' + t;
        cout << solve() << "\n";
    }
};