/**
 * @Time : 2025/3/16-3:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P3812 线性基 模版
 */
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, M = 50;
ll T, n, a[55], basis[55];

void init1() {
    for(int j = 1; j <= n; j++) {
        ll num = a[j];
        for(int i = M; i >= 0; i--) {
            if((num & (1ll << i)) == 0) continue;
            if(basis[i] == 0) {
                basis[i] = num;
                break;
            } else num ^= basis[i];
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        init1();
        ll ans = 0;
        for(int i = M; i >= 0; i--)
            ans = max(ans, ans ^ basis[i]);
        cout << ans;
    }
}