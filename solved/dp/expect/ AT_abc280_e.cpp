/**
 * @Time : 2023/12/21-11:01 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
long long n, p, inv;

long long q_pow(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(1 & b) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    inv = q_pow(100, mod - 2);
    cin >> n >> p;
    vector<long long> cache(n + 1, -1);
    function<long long(long long)> dfs = [&](long long num) -> long long {
        if(num <= 0) return 0;
        if(cache[num] != -1) return cache[num];
        long long res = dfs(num - 2) * p + dfs(num - 1) * (100 - p);
        res = (res % mod * inv % mod + 1) % mod;
        cache[num] = res;
        return res;
    };
    cout << dfs(n) << endl;
}