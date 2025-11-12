/**
 * @Time : 2024/6/21-3:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1328B 模拟
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, k;

void solve() {
    ll sum = 0, c1 = 2;
    while(sum + (c1 - 1) < k) {
        sum += (c1 - 1);
        c1++;
    }
    ll c2 = k - sum;
    string s(n, 'a');
    s[c1 - 1] = s[c2 - 1] = 'b';
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        solve();
    }
};