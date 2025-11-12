/**
 * @Time : 2023/12/27-10:17 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, a[N], b[N];

bool check(long long r) {
    int i = 1, j = 1;
    while(i <= n && j <= m) {
        if(a[i] < b[j] - r) return false;
        if(b[j] + r < a[i]) j++;
        else i++;
    }
    return i == n + 1;
}

void solve() {
    long long lo = 0, hi = 2e9;
    while(lo < hi) {
        long long mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++)
        cin >> b[i];
    solve();
}