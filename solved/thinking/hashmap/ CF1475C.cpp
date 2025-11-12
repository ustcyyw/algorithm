/**
 * @Time : 2024/7/8-4:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1475C 哈希表计数
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, n1, n2, k, a[N], b[N];

void solve() {
    map<ll, int> boy, girl, comm;
    ll ans = 0;
    for(int i = 1; i <= k; i++) {
        int num1 = a[i], num2 = b[i];
        ll key = (ll)num1 * N + num2;
        ans += i - 1 - boy[num1] - girl[num2] + comm[key];
        boy[num1]++, girl[num2]++, comm[key]++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n1 >> n2 >> k;
        for(int i = 1; i <= k; i++)
            cin >> a[i];
        for(int i = 1; i <= k; i++)
            cin >> b[i];
        solve();
    }
};