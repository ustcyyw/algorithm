/**
 * @Time : 2024/12/26-11:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1669H 1300 贪心 位运算
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k, cnt[32];

void solve() {
    int ans = 0;
    for(int j = 30; j >= 0; j--) {
        if(k + cnt[j] >= n) {
            ans |= 1 << j;
            k -= n - cnt[j];
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        memset(cnt, 0, sizeof(cnt));
        for(ll i = 1, num; i <= n; i++) {
            cin >> num;
            for(int j = 0; j < 31; j++)
                if(num & (1 << j))
                    cnt[j]++;
        }
        solve();
    }
};