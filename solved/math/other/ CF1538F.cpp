/**
 * @Time : 2024/7/11-9:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1538F 找规律
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, lo, hi;

ll count(int num) {
    ll ans = 0, p = 1;
    for(int i = 1; ; i++, p *= 10) {
        int c1 = (num + 1) / (p * 10);
        ans += ((num + 1) / p - c1) * i;
        if(num / p == 0) break;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> lo >> hi;
        cout << count(hi - 1) - count(lo - 1) << "\n";
    }
};