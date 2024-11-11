/**
 * @Time : 2024/6/13-11:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1879D 拆位 + 前缀和
 */
 /*
  * 位运算中常见的拆位思路
  * 具体到某一位的计算 需要统计1出现次数的奇偶。
  * 如果截止目前i出现了奇数次1，那么就要求前缀pre处出现了偶数次1
  * 于是nums[pre + 1, i]上这一位共出现了奇数次1 异或和为1 对答案的贡献就可以计算了
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, nums[N];

ll cal(int j) {
    ll base = pow(2, j);
    // 分别记录前缀中1出现奇数次/偶数次的次数，以及对应的位置的前缀和
    ll odd = 0, even = 1, os = 0, es = 0, ans = 0;
    for(int i = 1, cnt = 0; i <= n; i++) {
        cnt += ((1 << j) & nums[i]) > 0;
        if(cnt % 2 == 1) { // 当前1出现了奇数次 要求前缀1出现偶数次
            odd++, os += i;
            ans = (ans + (i * even - es) % mod * base % mod) % mod;
        } else {
            even++, es += i;
            ans = (ans + (i * odd - os) % mod * base % mod) % mod;
        }
    }
    return ans;
}

void solve() {
    ll ans = 0;
    for(int i = 0; i < 32; i++)
        ans = (ans + cal(i)) % mod;
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
    }
    solve();
};