/**
 * @Time : 2024/9/8-11:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1846D 数学 计算几何
 */
 /*
  * 通过相似算重叠部分所成的梯形的高和上底即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n;
long double d, h, height[N];

void solve() {
    long double bs = h * d * 0.5, ans = bs;
    for(int i = 1; i < n; i++) {
        long double h1 = height[i + 1] - height[i];
        if(h1 >= h) ans += bs;
        else ans += (2 * d - h1 * d * 1.0 / h) * h1 * 0.5;
    }
    printf("%.12Lf\n", ans);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> d >> h;
        for(int i = 1; i <= n; i++)
            cin >> height[i];
        sort(height, height + n + 1);
        solve();
    }
};