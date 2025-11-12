/**
 * @Time : 2023/12/13-1:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, p, a[N], b[N];
long long sum[N];

void solve() {
    sort(a, a + n), sort(b, b + m);
    for(int i = 1; i <= m; i++)
        sum[i] = sum[i - 1] + b[i - 1];
    long long res = 0;
    for(int i = 0, j = m - 1; i < n; i++) {
        while(j >= 0 && a[i] + b[j] > p) j--;
        res += (long long)a[i] * (j + 1) + (long long)p * (m - j - 1) + sum[j + 1];
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> p;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < m; i++)
        cin >> b[i];
    solve();
};