/**
 * @Time : 2025/3/16-11:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF808C 1400 构造算法
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 63;
ll T, n, w, ans[105];
vector<vector<ll>> infos;

void solve() {
    if(w < 0) {
        cout << -1;
        return;
    }
    for(int i = n - 1; w && i >= 0; i--) {
        int a = infos[i][0], id = infos[i][1];
        int t = min(w, a - ans[id]);
        w -= t, ans[id] += t;
    }
    for(int i = 0; i < n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> w;
        for(int i = 0, a; i < n; i++) {
            cin >> a;
            infos.push_back({a, i});
            w -= (a + 1) / 2, ans[i] = (a + 1) / 2;
        }
        sort(infos.begin(), infos.end());
        solve();
    }
}