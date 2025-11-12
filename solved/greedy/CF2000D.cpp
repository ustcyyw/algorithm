/**
 * @Time : 2024/11/22-8:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2000D 贪心 前缀和 双指针 1200
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
ll T, n, sum[N];
string s;

void solve() {
    ll ans = 0;
    for(int i = 1, j = n; i < j; i++, j--) {
        while(i < j && s[i] == 'R') i++;
        while(j > i && s[j] == 'L') j--;
        if(i != j) ans += sum[j] - sum[i - 1];
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum[i] = sum[i - 1] + num;
        }
        cin >> s;
        s = '.' + s;
        solve();
    }
};