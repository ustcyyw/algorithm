/**
 * @Time : 2025/3/20-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF920B 1200 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, M = 1e6 + 5;
int T, n, m, ans[N];
vector<vector<int>> infos;

void solve() {
    for(int i = 0, time = 0; i < n; i++) {
        time = max(time, infos[i][0]);
        if(time <= infos[i][2]) {
            ans[infos[i][1]] = time;
            time++;
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        infos = {};
        fill(ans, ans + n + 1, 0);
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            infos.push_back({l, i, r});
        }
        sort(infos.begin(), infos.end());
        solve();
    }
}