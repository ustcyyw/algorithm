/**
 * @Time : 2024/5/14-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1165D 数学 数论
 */
 /*
  * 每个数的因子都是成对出现 一大一小（平方数特殊一点）
  * 因此如果答案存在 一定 = 最小因子 * 最大因子
  * 剩下就是检验其它成对的因子相乘是否等于这个数 这个数的因子是否展示全
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 305, mod = 998244353;
int T, n, a[N];

void solve() {
    sort(a + 1, a + n + 1);
    ll num = (ll)a[1] * a[n];
    for(int i = 2, j = n - 1; i <= j; i++, j--) {
        ll t = (ll)a[i] * a[j];
        if(t != num) {
            cout << -1 << "\n";
            return;
        }
    }
    int cnt = 0;
    for(int i = 2; i <= (int)sqrt(num); i++) {
        if(num % i == 0) {
            if((ll)i * i != num) cnt += 2;
            else cnt++;
        }
    }
    cout << (cnt == n ? num : -1) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        solve();
    }
};