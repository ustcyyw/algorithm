/**
 * @Time : 2024/4/11-11:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
ll T, n, k, a[N];

void solve() {
    // 都是先攻击首个位置的船
    int ans = 0;
    for(int i = 1, j = n; i <= j; ) {
        int t = min(a[i], a[j]);
        if(k < t || (i != j && k < 2 * t - 1)) break; // 不够击毁任何一个船
        a[i] -= t, a[j] -= t - 1, k -= 2 * t - 1;
        if(a[i] > 0) {
            if(k == 0) break; // 不够击毁最后一个船
            k--, ans++, j--; // 击毁最后一个船
        } else {
            ans++, i++;
            if(k == 0) break;
            a[j]--, k--; // 保证下一次还是先攻击第一个船
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >>  k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        solve();
    }
};