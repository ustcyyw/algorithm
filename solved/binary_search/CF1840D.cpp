/**
 * @Time : 2024/9/6-11:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1840D 二分答案
 */
 /*
  * 最大值最小的经典模版
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, k, a[N];

int find(int diff, int start) {
    int i = start;
    while(i <= n && a[i] - a[start] <= diff) i++;
    return i;
}

bool check(int diff) {
    int idx1 = find(diff, 1), idx2 = find(diff, idx1);
    return find(diff, idx2) == n + 1;
}

void solve() {
    int lo = 0, hi = 1e9;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(2 * mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a, a + n + 1);
        solve();
    }
};