/**
 * @Time : 2025/2/28-11:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF818B 1600 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, mod = 1e9 + 7;
ll T, n, m, a[105], l[105], marked[105];

bool solve() {
    for(int i = 1; i < m; i++) {
        int lo = l[i], hi = l[i + 1];
        int d = lo < hi ? hi - lo : n - lo + hi;
        if(d == 0 || d > n || (marked[d] && a[lo] != d)) return false;
        if(a[lo] != 0 && a[lo] != d) return false;
        marked[d] = 1;
        a[lo] = d;
    }
    for(int i = 1, j = 1; i <= n; i++) {
        if(a[i] != 0) continue;
        while(j <= n && marked[j]) j++;
        marked[j] = 1, a[i] = j;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> l[i];
    if(!solve()) cout << "-1";
    else {
        for(int i = 1; i <= n; i++)
            cout << a[i] << " ";
    }
}