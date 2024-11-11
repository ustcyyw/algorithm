/**
 * @Time : 2024/5/14-10:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * a是质数：找第a个质数，比自身大
 * a不是质数 找其最大因子（非自身）比自身小
 *
 * 那么最大的数 只能是来自于原本的数组或者是第k个质数、
 * 是质数 倒推原本的数；否则它就是原本的数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2750131 + 5, mod = 998244353;
int T, n, k, c, d;
multiset<int> nums;
unordered_map<int, int> order;
vector<int> prime;

int init = []() -> int {
    vector<int> isPrime(N + 1, 1);
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) {
            prime.push_back(i);
            order[i] = prime.size();
        }
        for (int j = 0; j < prime.size() && (ll)i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

int findFactor(int num) {
    for(int a : prime) {
        if(num % a == 0)
            return num / a;
    }
    return -1;
}

void solve() {
    while(!nums.empty()) {
        int maxV = *nums.rbegin(), av = -1, gv = -1; // 考虑最大值
        if(order.count(maxV)) { // 是质数的情况
            av = order[maxV];
            gv = maxV;
        } else {
            av = maxV;
            gv = findFactor(maxV);
        }
        nums.erase(nums.find(av)), nums.erase(nums.find(gv));
        cout << av << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= 2 * n; i++) {
        cin >> num;
        nums.insert(num);
    }
    solve();
};