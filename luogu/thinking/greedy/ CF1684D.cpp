/**
 * @Time : 2024/6/13-4:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1684D 思维 + 贪心
 */
 /*
  * 肯定是要用完才好 因为把最后k个陷阱跳过 一定好于有不用完的
  * 假设k个跳过的陷阱下表从左往右下标依次是 i1,i2...,i[k-1],i[k]
  * 那么选择跳过他们 会导致后续增加的伤害依次为 （其右边一共有n-i个陷阱，其中还有一部分被跳过了）
  * n - i1 - (k - 1)
  * n - i2 - (k - 2)
  * n - i3 - (k - 3)
  * ....
  * n - i[k-1] - 1
  * n - i[k]
  * 以上进行求和为
  * nk - sum(i[1, k]) - (k-1) * k / 2 = nk - (k-1) * k / 2 - sum(i[1, k])
  * 用total表示原本陷阱的总伤害 那么跳过k个陷阱的总伤害为
  * total + nk - (k-1) * k / 2 - (sum(i[1, k]) + sum(ai))
  * = total + nk - (k-1) * k / 2 - sum(i + ai)
  * 要使总伤害最小 total, nk, - (k-1) * k / 2都是固定值
  * 只能让sum(i + ai)最大 那就是选出i + ai最大的k个陷阱即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, k, a[N], b[N];

void solve() {
    ll sum = accumulate(a + 1, a + n + 1, 0ll);
    sum += n * k - (k - 1) * k / 2;
    sort(b + 1, b + 1 + n);
    ll temp = accumulate(b + n - k + 1, b + 1 + n, 0ll);
    cout << sum - temp << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> a[i];
            b[i] = a[i] + i;
        }
        solve();
    }
};