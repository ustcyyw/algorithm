/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, p[N], mp[N];

void solve() {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(p[i] == i || p[p[i]] == i) continue;
        int j1 = mp[i], j2 = p[i], num = p[j2];
        mp[num] = j1;
        swap(p[j1], p[j2]);
        cnt++;
    }
    cout << cnt << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> p[i];
            mp[p[i]] = i;
        }
        solve();
    };
};