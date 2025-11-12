/**
 * @Time : 2025/3/5-9:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF846A 1500 暴力枚举 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 5000 + 5, P = 13331;
ll n, sum[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        sum[i] = sum[i - 1] + num;
    }
    int ans = n;
    for(int i = 0; i <= n; i++) {
        int temp = sum[i] + n - i - (sum[n] - sum[i]);
        ans = min(ans, temp);
    }
    cout << n - ans << "\n";
}