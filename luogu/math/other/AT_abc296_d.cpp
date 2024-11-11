/**
 * @Time : 2023/8/28-3:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
long long n, m;

long long solve() {
    long long up = (int)sqrt(m);
    if(n >= m || up * up == m) return m;
    long long res = LONG_LONG_MAX;
    for(long long i = m / n; i <= min(up + 1, n); i++){
        long long t = m / i;
        if(t > n) continue;
        if(m % i == 0) return m;
        if(t + 1 <= n)
            res = min(res, (long long)i * (t + 1));
    }
    return res == LONG_LONG_MAX ? -1 : res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    cout << solve() << endl;
}