/**
 * @Time : 2024/3/7-4:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 将两种距离的表达式平方 在相等时有
 * (x1 - x2) ^ 2 + (y1 - y2) ^ 2
 * = abs(x1 - x2) ^ 2 + abs(y1 - y2) ^ 2 + 2 * abs(x1 - x2) * abs(y1 - y2)
 * 绝对值平方 可以将绝对值符号去掉
 * 于是上述化简为 2 * abs(x1 - x2) * abs(y1 - y2) = 0
 * 相等于要找x1 = x2 或者 y1 = y2的点
 * 用hashmap记录x坐标和y坐标出现的次数 但是要注意如果两个点x和y坐标都相同就会计算重复
 * 还要针对这部分去重 可以用第三个hashmap记录坐标值
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
ll T = 1e9 + 5, n, x, y;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    ll res = 0ll;
    unordered_map<ll, int> xm, ym, pm;
    for(int i = 0; i < n; i++) {
        cin >> x >> y;
        res += xm[x] + ym[y] - pm[x * T + y];
        xm[x]++, ym[y]++, pm[x * T + y]++;
    }
    cout << res << "\n";
};