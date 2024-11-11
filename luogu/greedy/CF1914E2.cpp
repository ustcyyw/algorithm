/**
 * @Time : 2024/11/7-8:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1914E2 贪心
 */
 /*
  * 甲选一个 差值由a[i] - b[i] 变为 a[i] - 1
乙选一个 差值由a[i] - b[i] 变为 -b[i] + 1

甲选择a[i]的变化 a[i] + b[i] - 2 要让其尽可能大
乙选择a[i]的变化为 -b[i] - a[i] + 2 要让其尽可能小 就要让b[i] + a[i]大
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
ll T, n, a[N], b[N];

void solve() {
    priority_queue<vector<ll>> pq;
    for(int i = 1; i <= n; i++)
        pq.push({a[i] + b[i], i});
    for(int i = 1; i <= n; i += 2) {
        int j = pq.top()[1];
        pq.pop();
        a[j]--, b[j] = 0;
        if(!pq.empty()) {
            j = pq.top()[1];
            pq.pop();
            b[j]--, a[j] = 0;
        }
    }
    cout << accumulate(a + 1, a + n + 1, 0ll) - accumulate(b + 1, b + n + 1, 0ll) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        solve();
    }
};