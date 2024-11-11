/**
 * @Time : 2024/9/22-9:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1878F 数论
 */
/*
  * 是否存在一个数a与n互质 并且 d(n * a) = n
n的因子数量是d1，a的因子数量是d2 那么 n * a 的因子数量是 d1 * d2 = n
a的因子数量为 d2 = n / d1 要求n能被d1整除
a和n互质 并且只关注因子数量 并不关注a的大小 质数数量无限多 所以并不用考虑用什么质数来构建a
只需要考虑规定因子数量为d2的情况下 能不能选出特定数量的质数 让a的因子数量为d2

给定质因子的情况 用乘法原理可知 质因子分别出现了 cnt1, cnt2, cnt3个
那么总的因子数量就是 (cnt1 + 1) * (cnt2 + 1) * (cnt3 + 1) * ...
d1的数量即可根据此进行计算（在操作过程中维护n的质因子统计情况即可）
d2进行因式分解 就可以倒推出a的质因子构成情况
但具体构成不必关注 总之给定d2 一定能有一组质因子与之对应 因此只要n能被d1整除 本题答案就是yes

  本实现中 关于 n 整除 d1，通过质因子出现的统计情况来判断
  另外一种实现则是通过公式 a * b % p = (a % p * b % p) % p
  因此可以记录操作过程中乘上的所有x，累乘的过程中不断对d1取mod
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 998244353;
int T, q, base, n;
unordered_map<int, int> st; // 统计n的质因子数量

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
void change(unordered_map<int, int>& mp, int x) {
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
    // 计算d1 也是根据统计d1的质因子情况 题目保证d1 <= 1e9
    int d1 = 1;
    for(auto& p : st)
        d1 *= p.second + 1;
    unordered_map<int, int> dmp;
    change(dmp, d1);
    for(auto& p : dmp) { // 计算n是否能整除d1
        int num = p.first, cnt = p.second;
        if(cnt > st[num]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> base >> q;
        st.clear(), change(st, base);
        for(int i = 1, t, x; i <= q; i++) {
            cin >> t;
            if(t == 1) {
                cin >> x;
                change(st, x);
                cout << (check() ? "YES" : "NO") << "\n";
            } else st.clear(), change(st, base);
        }
        cout << "\n";
    };
};