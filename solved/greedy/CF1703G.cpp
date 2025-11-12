/**
 * @Time : 2024/2/4-8:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 如果固定了好钥匙的使用次数 坏钥匙肯定是越往后用越好 这样减半的才越少
  * 因此枚举好钥匙的使用次数i，相应的金币用前缀和求出
  * 而后缀 每个元素得除以2 ^ (n - i)。 每多用一次坏钥匙 后缀中每个元素 / 2
  * 除2操作 相当于二进制位右移1位。
  * 可以通过拆位 记录二进制每一位出现了多少1 多用一次坏钥匙就将这些二进制位右移
  * 最后将统计的二进制位再折算成数字和即可。
  */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1e5 + 5;
int T, n, cnt[32];
ll k, nums[N], sum[N];

ll half(ll num) {
    for(int i = 0; i < 31; i++)
        cnt[i] = cnt[i + 1];
    ll ans = 0;
    for(int i = 0; i < 32; i++) {
        ll t = 1ll << i;
        if(num & t) cnt[i]++;
        ans += t * cnt[i];
    }
    return ans;
}

void solve() {
    memset(cnt, 0, sizeof(cnt));
    ll res = sum[n] - k * n;
    for(int i = n - 1; i >= 0; i--) { // sum[1, i]上用好钥匙 sum[i+1, n]上用坏钥匙
        ll t = half(nums[i + 1] / 2) + sum[i] - k * i;
        res = max(res, t);
    }
    cout << res << "\n";
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    sum[0] = 0;
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = nums[i] + sum[i - 1];
        }
        solve();
    }
};