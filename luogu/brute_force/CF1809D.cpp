/**
 * @Time : 2024/12/10-3:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1809D 1800 暴力枚举 贪心
 */
 /*
  * 本题给的操作花费 但凡多一次操作 都会增加巨大花费
  * 所以应该考虑的是 操作次数少 在操作次数确定的情况下 才考虑优先使用交换操作
  *
  * 可以进行交换操作和删除操作 并且删除涉及到删0还是1 变量太多
  * 考虑枚举删除1的数量
  * 在删除的1的数量是固定的情况下 肯定优先删除靠左的1
  * 然后就只能进行 交换或者删0两种操作
  * 对于某一个0 如果其左边有2个及以上的1 直接删掉更好；如果只有1个1，选择交换
  * 由于左边已经删了cnt个1，此时左边还剩1个1的0一开始左边有(cnt + 1)个1
  * 而此时左边还剩2个及以上1的0，一开始有(cnt + 2)及以上个1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int T, n;
string s;

void solve() {
    vector<int> arr(n + 2, 0), sum(n + 2, 0);
    for(int i = 1, one = 0; i <= n; i++) {
        if(s[i] == '1') one++;
        else arr[one]++; // 左边有one个1的0计数+1
    }
    sum[0] = arr[0];
    for(int i = 1; i <= n + 1; i++)
        sum[i] = sum[i - 1] + arr[i];
    // 枚举i使得[0,i]上的1被删除 相当于枚举了删除的1的数量
    ll ans = LONG_LONG_MAX, a = (ll)1e12, b = a + 1;
    for(int i = 0, cnt = 0; i <= n; i++) {
        if(s[i] == '1') cnt++;
        int ta = arr[cnt + 1], tb = sum[n + 1] - sum[cnt + 1];
        ans = min(ans, a * ta + (cnt + tb) * b);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> s;
        n = s.size();
        s = '.' + s;
        solve();
    }
};