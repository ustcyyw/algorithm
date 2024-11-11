/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
/*
 * 查看是否存在公共的质因子即可
 *
 * 因为最大的数MAX = 1e9，找因子从2枚举到sqrt(MAX)
 * 因此质因数分解的时候 也只需要处理[2, sqrt(MAX)]上的质因子
 * 不过要注意这部分质因子检查完成后 不排除还剩一个很大的质因子
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 31700, M = 1e5 + 5;
int n, T, nums[M];

vector<int> prime;
int init = []() {
    vector<int> isPrime(N + 1, 1);
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

unordered_set<int> factors(int num) { // 进行因式分解
    int m = prime.size(), i = 0;
    unordered_set<int> res;
    while(i < m && num > 1 && num >= prime[i]) {
        if(num % prime[i] == 0) {
            num /= prime[i];
            res.insert(prime[i]);
        } else i++;
    }
    if(num > 1) res.insert(num); // num > 1 那么剩下的这个num本身就是一个质因子
    return res;
}

string solve() {
    set<int> set;
    for(int i = 0; i < n; i++) {
        if(nums[i] == 1) continue;
        for(int num : factors(nums[i])) {
            if(set.count(num)) return "YES";
            set.insert(num);
        }
    }
    return "NO";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        cout << solve() << endl;
    }
};