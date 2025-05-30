/**
 * @Time : 2025/5/29-20:39
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 一系列的乘法，除法，除法必须除尽
  * x分解质因子   a1 * a2 * ... am
  * y分解质因子   b1 * b2 * ... bn
  * 交集为c = gcd(x, y)
  * 不在c中的ai 要用除法去掉
  * 不在c中的bi 要用乘法获取
  *
  * 将num用1～k中的数分解出来
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
int T, x, y, k, cache[M];

vector<int> prime, isPrime(M, 1);
int init = []() {
    for (int i = 2; i < M; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < M; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

int cal(int num) {
    if(num == 1) return 0;
    if(num <= k) return 1;
    if(isPrime[num] && num > k) return -1;
    if(cache[num] != 0) return cache[num];
    int ans = INT_MAX;
    for(int i = 2; i <= min((int)sqrt(num), k); i++) {
        if(num % i != 0) continue;
        int temp = cal(num / i);
        if(temp != -1) ans = min(ans, temp + 1);
    }
    ans = ans == INT_MAX ? -1 : ans;
    return cache[num] = ans;
}

int solve() {
    int c = gcd(x, y), num1 = x / c, num2 = y / c;
    fill(cache, cache + max(num1, num2) + 1, 0);
    int t1 = cal(num1), t2 = cal(num2);
    if(t1 == -1 || t2 == -1) return -1;
    return t1 + t2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> x >> y >> k;
        cout << solve() << "\n";
    }
}