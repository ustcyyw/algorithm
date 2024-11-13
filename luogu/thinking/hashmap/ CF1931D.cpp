/**
 * @Time : 2024/11/12-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1931D hashmap计数
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, A = 1e9 + 1;
int T, n, x, y;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> x >> y;
        map<ll, int> map;
        ll ans = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            int mx = num % x, my = num % y;
            ans += map[(ll)(x - mx) % x * A + my];
            map[(ll)mx * A + my]++;
        }
        cout << ans << "\n";
    }
};