/**
 * @Time : 2025/2/11-10:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065E 构造 猜结论
 */
 /*
  * 0有x个，1有y个 这两字符地位平等 不妨假设x > y
  * 1. x < k，所有单一数字放在一个子串 就是最大平衡值 也达不到要求
  * 2. x很大 x - y > k，整个字符串的平衡值已经超过k 最大平衡值肯定也超过k
  * 除此之外 先从极端情况开始考虑 将字符k个放在一起是否可行？
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5;
ll T, n, m, k;
char c1, c2;

string solve() {
    if(abs(n - m) > k || max(n, m) < k) return "-1";
    string ans;
    while(n || m) {
        for(int i = 0; i < k && n; i++, n--)
            ans.push_back(c1);
        for(int i = 0; i < k && m; i++, m--)
            ans.push_back(c2);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m >> k;
        c1 = '0', c2 = '1';
        if(n < m) swap(c1, c2), swap(n, m);
        cout << solve() << "\n";
    }
};