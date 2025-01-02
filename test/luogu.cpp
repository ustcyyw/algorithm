/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e3 + 5, mod = 998244353;
int T, n, m, first[N], last[N], f1, l1;
map<int, int> mp;

void solve() {
    int ans = 1;
    for(int f = 1; f <= n; f++) {
        for(int l = 1; l <= n; l++) {
            if(l == f || (f1 == f && l1 == l)) continue;
            int c2 = mp[f * N + l], c1 = first[f] + last[l] - 2 * c2;
            if(f1 != f && l1 != l) ans = max(ans, c2 + c1 + 1);
            else ans = max(ans, c2 + 1);
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1, f, l; i <= m; i++) {
            cin >> f >> l;
            if(i == 1) f1 = f, l1 = l;
            first[f]++, last[l]++, mp[f * N + l]++;
        }
        solve();
    }
};