/**
 * @Time : 2025/3/24-10:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF961B 1200 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 15, mod = 1e9 + 7;
int T, n, k, a[N], t[N], sumA[N], sumT[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= n; i++)
            cin >> t[i];
        for(int i = 1; i <= n; i++) {
            sumA[i] = sumA[i - 1] + a[i];
            sumT[i] = sumT[i - 1] + a[i] * t[i];
        }
        int ans = 0;
        for(int i = 1; i + k - 1 <= n; i++) {
            int j = i + k - 1;
            ans = max(ans, sumT[i - 1] + sumA[j] - sumA[i - 1] + sumT[n] - sumT[j]);
        }
        cout << ans << "\n";
    }
}