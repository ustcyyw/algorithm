/**
 * @Time : 2024/6/25-2:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1343C 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n;

void solve() {
    ll ans = 0, val = 0;
    for(ll i = 1, num, flag = 0; i <= n; i++) {
        cin >> num;
        if(flag == 0) {
            val = num;
            flag = num > 0 ? 1 : -1;
        } else {
            if((num > 0 && flag > 0) || (num < 0 && flag < 0)) val = max(val, num);
            else {
                ans += val, val = num;
                flag = num > 0 ? 1 : -1;
            }
        }
    }
    ans += val;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        solve();
    }
};