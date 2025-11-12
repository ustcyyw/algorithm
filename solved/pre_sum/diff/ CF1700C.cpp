/**
 * @Time : 2024/6/11-9:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1700C 差分数组
 */
/*
 * 类似的题还有lc1526题
 *
 * 看到让数组相等求最小操作数 并且操作是区间的+和-操作 可以考虑差分数组
 * 只要让差分数组除最后一个元素外都为0，那么原数组就相等了
 *
 * 数组相等 等价于差分数组 除了第d[n + 1]不为0以外 其它都为0
 * 1.d[1] += 1, d[n + 1] -= 1
 * 2.d[1] -= 1, d[i] += 1, 对任意i成立
 * 3.d[i] -= 1, d[n + 1] += 1, 对任意i成立
 *
 * 只有2操作可以让d[i]增大
 * 先通过2操作尽可能得让小于0的d[i]变为0
 * d[1] = 0了就使用操作1让d[1]增加 然后再用操作2让其它d[i] >= 0
 * 最后确保所有d[i]非0 再用操作3将他们减少为0即可
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, MV = 1e9;
typedef long long ll;
ll T, n, a[N], d[N] ;

void solve() {
    ll cnt = 0, neg = 0, pos = 0;
    if(d[1] < 0) cnt += abs(d[1]), d[1] = 0;
    for(int i = 2; i <= n; i++) {
        if(d[i] < 0) neg += d[i];
        else pos += d[i];
    }
    if(abs(neg) >= d[1]) {
        cnt += d[1], neg += d[1]; // 先通过2操作尽可能得让小于0的d[i]变为0
        cnt += abs(neg) * 2; // d[1] = 0了就使用操作1让d[1]增加 然后再用操作2让其它d[i] >= 0
    } else cnt += d[1]; // d[1] > abs(neg) 那么d1通过操作2就让所有d[i] >= 0, d[1]还剩的值使用操作3即可，所有总操作数就是d[1]
    cout << cnt + pos << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            d[i] = a[i] - a[i - 1];
        }
        solve();
    }
};