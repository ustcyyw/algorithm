/**
 * @Time : 2023/12/11-8:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, t, a[N], b[N], maxA;
long long sumB;

bool check(int val) {
    long long st = sumB;
    for(int i = 0; i < n; i++)
        if(a[i] <= val) st -= b[i];
    return st <= val;
}

void solve() {
    int lo = 1, hi = maxA;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> t;
    while(t-- > 0) {
        cin >> n;
        maxA = 0, sumB = 0;
        for(int i = 0; i < n; i++) {
            cin >> a[i];
            maxA = max(maxA, a[i]);
        }
        for(int i = 0; i < n; i++) {
            cin >> b[i];
            sumB += b[i];
        }
        solve();
    }
};