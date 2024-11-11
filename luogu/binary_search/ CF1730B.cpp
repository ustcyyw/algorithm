/**
 * @Time : 2023/12/26-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 最大值最小 二分
 * 如果最大值是val 那么 abs(x[i] - y) + t[i] <= val
 * abs(x[i] - y) <= val - t[i] = a
 * 就是说y离x[i]的距离小于等于a，那么y的范围一定是 [x[i] - a, x[i] + a]
 * n个不等式 如果能找到交集 就说明是可能的
 *
 * 算出最大值后 再通过不等式得到y的取值范围 此时肯定是一个点
 */
#include<bits/stdc++.h>
using namespace std;
typedef long double ld;
const int N = 1e5 + 5;
int T, n, x[N], t[N];

bool check(ld val) {
    ld l = -1e9, r = 1e9 ;
    for(int i = 0; i < n; i++) {
        ld a = val - t[i], lt = x[i] - a, rt = x[i] + a;
        l = max(l, lt), r = min(r, rt);
        if(r < l) return false;
    }
    return true;
}

void solve() {
    ld lo = 0, hi = 2e8;
    while(abs(lo - hi) > 1e-7) {
        ld mid = (lo + hi) / 2;
        if(check(mid)) hi = mid;
        else lo = mid;
    }
    ld l = -1e9, r = 1e9;
    for(int i = 0; i < n; i++) {
        ld a = lo - t[i], lt = x[i] - a, rt = x[i] + a;
        l = max(l, lt), r = min(r, rt);
    }
    printf("%Lf\n", l);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> x[i];
        for(int i = 0; i < n; i++)
            cin >> t[i];
        solve();
    }
}