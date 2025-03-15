/**
 * @Time : 2025/3/14-11:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF557B 1500 贪心 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, w, cups[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> w;
        for(int i = 1; i <= 2 * n; i++)
            cin >> cups[i];
        sort(cups + 1, cups + 2 * n + 1);
        long double t = min(cups[1] * 1.0, cups[n + 1] * 1.0 / 2);
        long double ans = min((long double)w, t * 3 * n);
        printf("%.10Lf", ans);
    }
}