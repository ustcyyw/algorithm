/**
 * @Time : 2024/7/10-11:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1538G
 */
/*
 * 数学题
 * 假设红色糖使用a个的礼包有x个
 * 那么使用了ax个红色糖，还剩下s1 - ax个
 * 使用了bx个蓝色糖，还剩下s2 - bx个
 * 这里有限制条件 x <= min(s1 / a, s2 / b)
 * 还剩的糖 用另外一种方式装礼盒 还能装 min((s1 - ax) / b, (s2 - bx) / a)
 * 所以总的能装 x + min((s1 - ax) / b, (s2 - bx) / a)
 * 这是一个可行域确定 找最值的问题 问题的解一定出现在可行域边缘点
 * 找直线 y1 = (s1 - ax) / b, y2 = (s2 - bx) / a 的交点。还有x = 0, x = min(s1 / a, s2 / b)
 * 注意 因为是离散的 所以直线交点计算出来后 要向上+1再计算一次
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, s1, s2, a, b;

ll y1(ll x) {
    return (s1 - a * x) / b;
}

ll y2(ll x) {
    return (s2 - b * x) / a;
}

ll total(ll x) {
    return x + min(y1(x), y2(x));
}

ll solve() {
    if(a == b) return min(s1 / a, s2 / a);
    ll t = min(s1 / a, s2 / b);
    ll t1 = total(0), t2 = total(t);
    ll xt = (b * s2 - a * s1) / (b * b - a * a);
    xt = max(0ll, xt), xt = min(t, xt);
    ll t3 = total(xt), t4 = total(min(t, xt + 1));
    return max({t1, t2, t3, t4});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s1 >> s2 >> a >> b;
        cout << solve() << "\n";
    }
};