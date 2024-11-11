/**
 * @Time : 2024/5/14-8:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1165E 数学 + 贪心
 */
/*
 * sum of (ai * bi * ci) ai和ci是固定的
 * 可以重排bi，那肯定将小的bi和大的 ai*ci放在一块
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int n, a[N], b[N];

void solve() {
    ll ans = 0;
    vector<ll> arr;
    for(int i = 1; i <= n; i++)
        arr.push_back((ll)a[i] * i * (n - i + 1));
    sort(arr.begin(), arr.end());
    sort(b + 1, b + n + 1);
    for(int i = 1; i <= n; i++)
        ans = (ans + arr[i - 1] % mod * b[n - i + 1] % mod) % mod;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    solve();
};