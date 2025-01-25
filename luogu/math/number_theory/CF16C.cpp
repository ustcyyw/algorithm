/**
 * @Time : 2025/1/24-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF16C 1800 数学
 */
/*
  * 假设长和宽分别减去了c1,c2后 比例成为 x:y
  * (a - c1) / (b - c2) = x / y
  * ay - c1*y = bx - c2*x
  * c2*x = bx - ay + c1*y
  * c1越大 c2也会越大 二者变化方向一致 为了让剩余面积最大 应当让c1和c2尽可能小
  * c2 = b - (a - c1) * y/x  （注意这里要化简到最简分数）
  * 因为c2必须是整数 那么 a - c1 必须是x的倍数 可以写成 a - c1 = kx 的形式
  * 要让 c1 = a - kx，要让c1尽可能小，k应该尽可能大 取 k <= a/x 的最大整数
  * a - c1 = kx, 那么 c2 = b - ky, 同理 k <= b/y
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 205, mod = 998244353;
int T, a, b, x, y;

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> a >> b >> x >> y;
        int g = gcd(x, y);
        x /= g, y /= g;
        int k = min(a / x, b / y);
        int c1 = a - k * x, c2 = b - k * y;
        cout << a - c1 << " " << b - c2 << "\n";
    }
};