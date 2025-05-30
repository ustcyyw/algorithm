/**
 * @Time : 2024/11/24-5:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1374D 数学
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> k;
        map<int, int> cnt;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(num % k != 0) cnt[k - num % k]++;
        }
        ll ans = 0;
        for(auto& p : cnt) {
            ans = max(ans, (ll)p.first + (ll)(p.second - 1) * k);
        }
        if(ans != 0) ans++;
        cout << ans << "\n";
    };
};