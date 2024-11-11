/**
 * @Time : 2024/7/8-3:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1475D 贪心
 */
 /*
  * CF1399E2的简单版本 贪心思路一致
  * https://codeforces.com/contest/1399/problem/E2
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, a[N], b[N];

int cal_two(priority_queue<int>& pq) {
    if(pq.empty()) return 0;
    int a1 = pq.top(); pq.pop();
    int res = a1 + (pq.empty() ? 0 : pq.top());
    pq.push(a1);
    return res;
}

void solve() {
    ll sum = accumulate(a + 1, a + n + 1, 0ll);
    if(sum < m) {
        cout << "-1\n";
        return;
    }
    priority_queue<int> pq1, pq2;
    for(int i = 1; i <= n; i++) {
        if(b[i] == 1) pq1.push(a[i]);
        else pq2.push(a[i]);
    }
    int ans = 0;
    while(m > 0) {
        if(!pq1.empty() && m - pq1.top() <= 0) {
            ans++;
            break;
        }
        int t = cal_two(pq1);
        if(pq2.empty() || t >= pq2.top()) {
            m -= pq1.top(), ans++;
            pq1.pop();
        } else {
            m -= pq2.top(), ans += 2;
            pq2.pop();
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> b[i];
        solve();
    }
};