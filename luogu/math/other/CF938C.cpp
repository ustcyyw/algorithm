/**
 * @Time : 2025/3/23-10:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF938C 1700 数学 构造算法 暴力枚举
 */
/*
 * 原问题是贪心问题，假设行和列每m个位置就得有1个0
 * 因为 总的0的数量为 n / m
 * 1的数量 cnt = n * n - (n / m) ^ 2 是一个平方差公式
 * (x + y) * (x - y) = cnt
 * 枚举 x - y 的值，求出x和y
 * n = x, y = n / m
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e6 + 15, mod = 1e9 + 7;
int T, cnt;

vector<int> solve() {
    if(cnt == 0) return {1, 1};
    for(int i = 1; i <= sqrt(cnt); i++) {
        if(cnt % i != 0) continue;
        int temp = cnt / i;
        if((temp + i) % 2 != 0) continue;
        int n = (temp + i) / 2, y = n - i;
        if(y == 0) continue;
        int m = n / y; // 注意 因为是离散的值 所以 m = n / y 之后 ，不一定就有 n / m = y
        if(m > 1 && m <= n && n / m == y) return {n, m};
    }
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> cnt;
        vector<int> ans = solve();
        if(ans[0] == -1) cout << "-1\n";
        else cout << ans[0] << " " << ans[1] << "\n";
    }
}