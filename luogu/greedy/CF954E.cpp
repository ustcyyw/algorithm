/**
 * @Time : 2025/3/19-9:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954E 2000 贪心 排序 数学（看了题目tag）
 */
/*
 * 将等式改写为 sum{xi * ti} - sum{xi * T} = 0
 * 将求和拆开为 x1(t1 - T) + x2(t2 - T) + ... + xn(xn - T) = 0
 * 令 ci = ti - T 为系数，是一个确定的数 并且有正有负 或者是0
 * 如果ci为0 那么对应的这一项全选即可
 * 最后求和为0，就是正数项之和 = 负数项之和
 * 按系数将进行分组
 * 负数部分更多，那几全选正数部分 并且正数部分为了让sum{xi}尽可能多 应该先选ci小的
 * 正数部分更多，那就全选负数部分 先选ci小的
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 15, mod = 1e9 + 7;
ll T, n, a[N], ps, ns, pos, neg, zero;
vector<vector<ll>> pArr, nArr;

ld pick(ld val, vector<vector<ll>>& arr) {
    ld ans = 0;
    sort(arr.begin(), arr.end());
    for(int i = 0; i < arr.size() && val > 0; i++) {
        ll c = arr[i][0], limit = arr[i][1], total = c * limit;
        ld need = min(val, (ld)total);
        ans += need / c, val -= need;
    }
    return ans;
}

void solve() {
    ld ans = 0;
    if(pos >= neg) {
        ans = ns + pick(neg * 1.0, pArr);
    } else {
        ans = ps + pick(pos * 1.0, nArr);
    }
    printf("%.10Lf\n", ans + zero);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> T;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1, t; i <= n; i++) {
        cin >> t;
        ll c = t - T, num = a[i] * c;
        if(c == 0) zero += a[i];
        if(c < 0) neg += -num, ns += a[i], nArr.push_back({-c, a[i]});
        if(c > 0) pos += num, ps += a[i], pArr.push_back({c, a[i]});
    }
    solve();
}