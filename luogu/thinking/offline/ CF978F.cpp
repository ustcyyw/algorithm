/**
 * @Time : 2024/11/15-11:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF978F 离线思想 模拟 1500
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, ans[N], val[N], cnt[N];
vector<vector<int>> codes,  conflicts;

void solve() {
    for(int i = 0, j = 0; i < n; ) {
        int v = codes[i][0], base = i; // v当前人的能力值，base所有能力值更低的人数
        while (i < n && codes[i][0] == v) {
            int idx = codes[i][1];
            ans[idx] = base - cnt[idx];
            i++;
        }
        while(j < m && val[conflicts[j][0]] <= v) {
            cnt[conflicts[j][1]]++;
            j++;
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> val[i];
        codes.push_back({val[i], i});
    }
    sort(codes.begin(), codes.end());
    for(int i = 1, a, b; i <= m; i++) {
        cin >> a >> b;
        if(val[a] > val[b]) swap(a, b);
        conflicts.push_back({a, b});
    }
    sort(conflicts.begin(), conflicts.end(), [](auto& a, auto& b) -> bool {
        return val[a[0]] < val[b[0]];
    });
    solve();
};