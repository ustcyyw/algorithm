/**
 * @Time : 2024/1/25-5:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 二分 + 差分
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long n, m, w, arr[N], diff[N], maxV;

bool check(long long val, long long k) {
    memset(diff, 0, sizeof(diff));
    for(long long sum = 0, i = 0; i < n; i++) {
        sum += diff[i];
        if(sum + arr[i] < val) {
            long long t = val - (sum + arr[i]);
            sum += t;
            diff[min(i + w, n + 1)] -= t;
            k -= t;
            if(k < 0) return false;
        }
    }
    return true;
}

void solve() {
    long long lo = 1, hi = maxV + m;
    while (lo < hi) {
        long long mid = (lo + hi + 1) >> 1;
        if(check(mid, m)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    maxV = 0;
    cin >> n >> m >> w;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        maxV = max(maxV, arr[i]);
    }
    solve();
}