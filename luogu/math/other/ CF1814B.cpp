/**
 * @Time : 2024/5/29-2:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1814B 数学
 */
/*
  * 假设使用了x次+1操作 m = x + 1
  * 总次数 x + a / (x + 1) + b / (x + 1) = (x + 1) + (a + b) / (x + 1) - 1
  * 要让这个式子最小 均值不等式
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e5 + 5;
typedef long long ll;
int T, n, x, y, ans;

int cal(ll pos, int a) {
    // 无法除尽一步的长度a时 可以在m增加到余数pos % a时 先走一次。 这样就能保证之后可以刚好走到
    int cnt = pos % a == 0 ? 0 : 1;
    return cnt + pos / a;
}

void solve() {
    int a = sqrt(x + y);
    for(int i = max(1, a - 10000); i <= a + 10000; i++)
        ans = min(ans, i - 1 + cal(x, i) + cal(y, i));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> x >> y;
        ans = INT_MAX;
        solve();
    }
};