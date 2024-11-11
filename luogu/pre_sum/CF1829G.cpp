/**
 * @Time : 2024/2/5-4:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 第一行有1个数 第二行有2个数 第2023行有2023个数 一共有2047276个数
  * 也就是说预处理出所有前缀和是可行的。
  * 第k个数在第几行？二分 求n * (n + 1) / 2 >= k的最小n
  * 然后确定在第几列 （n - 1) * n / 2是上一行的数 与k差多少 这个数就在第几列
  * 然后从这个点开始 向上 求和的边界是规律变化的。
  * 左边界-1，右边界不变。注意不要超出原本的边界。
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 2024;
ll T, k, sum[N][N];
int init = []() -> int {
    for(int i = 1; i < N; i++) {
        sum[i][0] = 0;
        ll num = (i - 1) * i / 2;
        for(int j = 1; j <= i; j++)
            sum[i][j] = sum[i][j - 1] + (num + j) * (num + j);
    }
    return 0;
}();

int get_row() {
    ll lo = 1, hi = N - 1;
    while(lo < hi) {
        ll mid = (lo + hi) >> 1, temp = mid * (mid + 1) / 2;
        if(temp >= k) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}

void solve() {
    int n = get_row(), m = k - (n - 1) * n / 2;
    int l = m, r = m;
    ll res = 0;
    while(n > 0) {
        res += sum[n][r] - sum[n][l - 1];
        n--;
        l = max(l - 1, 1), r = min(r, n);
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> k;
        solve();
    }
};