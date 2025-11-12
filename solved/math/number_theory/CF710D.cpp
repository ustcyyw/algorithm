/**
 * @Time : 2025/2/19-10:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF710D 2500 数学 数论 扩展欧几里得exgcd （cpp溢出 改用python处理了）
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5;
ll n, m, d1, a1, d2, a2, l, r;

/*
 * 计算序列1中第几项（c1）使得该项是两个序列中的公共数
 * a1 + c1 * d1 = a2 + c2 * d2
 * 整理方程
 * c1 * d1 - c2 * d2 = a, 其中a = a2 - a1
 * 形如 Ax + By = a 的方程为线性 Diophantine 方程
 * 要求解x和y，方程有解必须满足 a % gcd(A,B) = 0
 * c1 = a * x0 / g, c2 = -a * y0 / g
 */
int exgcd(int a, int b, int& x, int& y) {
    if (!b) {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

ll cal() {
    if(a1 == a2) return 0;
    ll a = a2 - a1, g = gcd(d1, d2);
    if(a % g != 0) return LONG_LONG_MIN;
    int x, y;
    exgcd(d1, d2, x, y);
    return -a * y / g;
}

ll findL(ll num, ll dd) {
    ll lo = -4e9, hi = 4e9;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1;
        if(num + mid * dd < l) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

ll findR(ll num, ll dd) {
    ll lo = -4e9, hi = 4e9;
    while(lo < hi) {
        ll mid = (lo + hi + 1) >> 1;
        if(num + mid * dd > r) hi = mid - 1;
        else lo = mid;
    }
    return lo;
}

ll solve() {
    l = max({l, a1, a2});
    if(l > r) return 0;
    ll c2 = cal();
    if(c2 == LONG_LONG_MIN) return 0;
    ll num = a2 + c2 * d2, dd = lcm(d1, d2);
    ll lo = findL(num, dd), hi = findR(num, dd);
    return hi - lo + 1;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> d1 >> a1 >> d2 >> a2 >> l >> r;
    cout << solve();
};

/*
 * 附上ac的python代码
import math

# 扩展欧几里得算法
def exgcd(a, b):
    if b == 0:
        return a, 1, 0
    d, x1, y1 = exgcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return d, x, y


# 计算 c2
def cal(a1, a2, d1, d2):
    if a1 == a2:
        return 0
    a = a2 - a1
    g = math.gcd(d1, d2)
    if a % g != 0:
        return float('-inf')
    _, x, y = exgcd(d1, d2)
    return -a * y // g


# 二分查找最小值
def findL(num, dd, l):
    lo, hi = -int(4e9), int(4e9)
    while lo < hi:
        mid = (lo + hi) // 2
        if num + mid * dd < l:
            lo = mid + 1
        else:
            hi = mid
    return lo


# 二分查找最大值
def findR(num, dd, r):
    lo, hi = -int(4e9), int(4e9)
    while lo < hi:
        mid = (lo + hi + 1) // 2
        if num + mid * dd > r:
            hi = mid - 1
        else:
            lo = mid
    return lo


# 主解法
def solve(d1, a1, d2, a2, l, r):
    l = max(l, a1, a2)
    if l > r:
        return 0
    c2 = cal(a1, a2, d1, d2)
    if c2 == float('-inf'):
        return 0
    num = a2 + c2 * d2
    dd = d1 * d2 // math.gcd(d1, d2)
    lo = findL(num, dd, l)
    hi = findR(num, dd, r)
    return hi - lo + 1


# 主程序
if __name__ == '__main__':
    # 输入
    d1, a1, d2, a2, l, r = map(int, input().split())

    # 计算并输出结果
    print(solve(d1, a1, d2, a2, l, r))
 */