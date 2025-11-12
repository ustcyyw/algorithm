/**
 * @Time : 2024/1/31-9:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 举一些例子看看 发现和两个数之差的质因子相关
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 5;
int a, b, T, m, prime[10000];
vector<int> factors[N];

int init = []() {
    int n = (int) sqrt(N);
    vector<int> isPrime(n + 1, 1), aux;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i] == 1) aux.push_back(i);
        for (int j = 0; j < aux.size() && (long long)i * aux[j] <= n; ++j) {
            isPrime[i * aux[j]] = 0;
            if (i % aux[j] == 0)
                break;
        }
    }
    m = aux.size();
    for (int i = 0; i < m; i++)
        prime[i] = aux[i];
    return 0;
}();

vector<int> &f(int num) {
    if (!factors[num].empty()) return factors[num];
    int key = num;
    vector<int> res;
    for (int i = 0; i < m && num > 1 && num >= prime[i]; i++) {
        if (num % prime[i] == 0) {
            res.push_back(prime[i]);
            while (num % prime[i] == 0) num /= prime[i];
        }
    }
    if (num > 1) res.push_back(num);
    factors[key] = res;
    return factors[key];
};

int solve() {
    if (b - a == 1) return -1;
    int res = INT_MAX;
    for (int mod: f(b - a)) {
        if (b % mod == 0) return 0;
        res = min(res, mod - b % mod);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> a >> b;
        cout << solve() << "\n";
    }
};