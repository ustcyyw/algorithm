/**
 * @Time : 2024/12/3-11:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1980F1 1900 数据结构 贪心
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, m, k, a[N], b[N], ans[N];
map<int, int> mp;

void solve() {
    ll s = 0, left = 1, up = 1;
    for(auto& [r, i] : mp) {
        if(a[i] >= up) {
            ans[i] = 1;
            s += (r - left) * (n - up + 1);
            up = a[i] + 1, left = r;
        }
    }
    s += (m - left + 1) * (n - up + 1); // 最后到达终点的部分
    cout << s << "\n";
    for(int i = 1; i <= k; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> m >> k;
        mp = {};
        fill(ans, ans + k + 1, 0);
        for(int i = 1; i <= k; i++) {
            cin >> a[i] >> b[i];
            if(!mp.count(b[i]) || a[mp[b[i]]] < a[i]) mp[b[i]] = i;
        }
        solve();
    };
};