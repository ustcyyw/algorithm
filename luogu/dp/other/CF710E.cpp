/**
 * @Time : 2025/2/19-11:24 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF710E 2000 动态规划
 */
/*
  * 1->2 min(x,y)

2->3 x, y + x
2->4 x * x, y

3->4 x
3->5 2x, y+x
3->6 3x, y

4->5 x, y+3x
4->6 2x, y+2x
4->7 3x, y+x
4->8 4x, y

5->6 x, y+4x
5->7 2x, y+3x, 2x和4->7的3x(4->5->7)是一回事
5->8 3x, y+2x, 8肯定不是由5转移而来
5->9 4x, y+x
5->10 5x, y

6->11 y + x, 5x
6->10 y + 2x, 4x

3->5->7 min(2x, y+x) + 2x
y + 3x
3->4->7 x + min(3x, y+x)
y + 2x
  举例发现 i 转移到 2 * i, 2 * i - 1, i + 1 才是有效的， 转移到其它状态都不是最优的 就不用计算了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e7 + 5;
ll n, x, y;

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> x >> y;
    vector<ll> dp(n + 2, LONG_LONG_MAX);
    dp[1] = x;
    for(int i = 1; i <= n; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + x);
        if(i * 2 <= n) dp[i * 2] = min(dp[i * 2], dp[i] + y);
        if(i * 2 - 1 <= n) dp[i * 2 - 1] = min(dp[i * 2 - 1], dp[i] + y + x);
    }
    cout << dp[n];
};