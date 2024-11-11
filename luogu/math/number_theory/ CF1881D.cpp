/**
 * @Time : 2024/9/23-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1881D 数论
 */
 /*
  * 统计质因数的个数 看是否能n等分
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 998244353;
int T, n;
unordered_map<int, int> mp;

vector<int> prime, isPrime;
int init = []() {
    isPrime.assign(N + 1, 1);
    for (int i = 2; i < N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();
// 分解并统计质因数
void count(int x) {
    for(int i = 0; i < prime.size() && x > 1; i++) {
        int num = prime[i], cnt = 0;
        while(x > 1 && x % num == 0) {
            cnt++, x /= num;
        }
        mp[num] += cnt;
        if(x > 1 && isPrime[x]) {
            mp[x]++;
            break;
        }
    }
}

bool check() {
    for(auto& p : mp) {
        if(p.second % n != 0)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        mp = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            count(num);
        }
        cout << (check() ? "YES" : "NO") << "\n";
    }
};