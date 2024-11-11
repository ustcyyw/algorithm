/**
 * @Time : 2024/7/19-2:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1607G 贪心
 */
/*
  * 每道菜都要吃m的总量 每道菜选择吃的数量 求最终剩余的食物之差的最小差值
  * 要吃的食物一共有 n * m, 两种食物分别有 sum1, sum2
  * 要让差值最小 两个食物最好都剩得一样多 假设剩余的食物为left
  * 要吃掉的 sum1 - left, sum2 - left
  * sum1 + sum2 - 2left = n * m
  * left = (sum1 + sum2 - n * m) / 2
  *
  * 特殊地 如果 sum1 - n * m >= sum2, 就都吃第一个食物；反之 sum2 - n * m >= sum1 都吃第二个食物
  * 除此之外 就不是全都吃一种的情况 那么left的值就有意义了
  * sum1 - left, sum2 - left 也有意义 这样就确定了要吃的数量
  * 限制条件下 如何取到指定值
  * max(0, m - bi) <= xi <= min(ai, m)
  * sum{xi} = eat, eat指的就是第一类食物要吃掉的个数
  * 我先保证每个xi都取最小值 然后和不太够 再挨个来看 怎么给xi加一些值
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, m, a[N], b[N], t1[N], t2[N], sum1, sum2, eat;

// 确定第一种食物吃多少
void cal_eat() {
    sum1 = accumulate(a + 1, a + n + 1, 0ll), sum2 = accumulate(b + 1, b + n + 1, 0ll);
    if(sum1 - m * n >= sum2) eat = n * m;
    else if(sum2 - m * n >= sum1) eat = 0;
    else {
        ll left = (sum1 + sum2 - n * m) / 2;
        eat = sum1 - left;
    }
}

void solve() {
    cal_eat();
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        t1[i] = max(0ll, m - b[i]), t2[i] = min(m, a[i]);
        sum += t1[i];
    }
    for(int i = 1; i <= n && sum < eat; i++) {
        int temp = min(eat - sum, t2[i] - t1[i]);
        sum += temp, t1[i] += temp;
    }
    cout << abs(sum1 - sum - (sum2 - (m * n - sum))) << "\n";
    for(int i = 1; i <= n; i++)
        cout << t1[i] << " " << m - t1[i] << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            cin >> a[i] >> b[i];
        solve();
    }
};