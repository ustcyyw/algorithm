/**
 * @Time : 2024/4/22-5:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, k, a[N];

bool check(int start) {
    for(int i = start, tm = m, sum = 0; i <= n; i++) {
        sum += a[i];
        if(sum > k) {
            tm--, sum = a[i];
            if(tm == 0) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << n + 1 - lo;
};