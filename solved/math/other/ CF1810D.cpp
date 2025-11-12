/**
 * @Time : 2024/6/4-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1810D 数学 + 二分
 */
/*
 * 能向上爬a 夜晚掉下来b 那么一天净爬了 a - b
 * 假设最后一天刚好爬了a到达终点
 * h1 = （a - b）* (n - 1) + a = n * a - (n - 1)b
 * 假设最后一天刚好爬了1米就到达终点 前一天掉了1米？那前一天就到了
 * 最后一天刚好爬了b米就到达终点 前一天掉了b米？那前一天就到了
 * 所以最后一天 至少要爬 b + 1 米
 * h2 = (a - b) * (n - 1) + b + 1 = (n - 1) * a - (n - 2) * b + 1
 * 因为 a >= b + 1 所以 h1 >= h2, 高就限制在[h2, h1]上了
 *
 * 给定a和b 以及h 计算天数
 * 二分天数 找最小的天数可以到达h  (a - b) * (day - 1) + a >= h
 * 那么这一天就是可以到达的
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55, MV = 1e9;
typedef long long ll;
ll T, n, q, t, a, b, h1, h2;

ll cal(ll h) {
    ll lo = 1, hi = h / (a - b) + 1;
    while(lo < hi) {
        ll day = (lo + hi) >> 1;
        if((a - b) * (day - 1) + a >= h) hi = day;
        else lo = day + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> q;
        h1 = 0, h2 = (ll)1e18;
        for(int i = 1; i <= q; i++) {
            cin >> t >> a >> b;
            if(t == 1) {
                cin >> n;
                ll t1 = (a - b) * (n - 1) + b + 1, t2 = (a - b) * (n - 1) + a;
                if(n == 1) t1 = 1, t2 = a; // 特殊处理n=1
                if(t2 < t1 || t1 > h2 || t2 < h1) cout << "0 "; // 判断是否矛盾
                else {
                    h1 = max(t1, h1), h2 = min(h2, t2);
                    cout << "1 ";
                }
            } else {
                ll d1 = cal(h1), d2 = cal(h2);
                cout << (d1 == d2 ? d1 : -1) << " ";
            }
        }
        cout << "\n";
    }
};