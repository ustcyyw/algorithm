/**
 * @Time : 2025/4/2-10:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF990E 2100 贪心 暴力枚举 数学 调和级数
 */
 /*
  * 位置0被占用、连续障碍的长度 > 最大功率 这两种情况都不可能完成
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e6 + 15, M = 30;
int n, m, k, s[N], a[N], pre[N];

int check() {
    if(s[1] == 0 && m > 0) return -1;
    int len = 0;
    for(int i = 1, j; i <= m; ) {
        j = i + 1;
        while(j <= m && s[j] == s[j - 1] + 1) j++;
        len = max(j - i, len);
        i = j;
    }
    return len < k ? len : -1;
}
// 计算过程中的跳跃 步长可以视为ck
ll cal(int ck) {
    ll cnt = 0;
    for(int x = 0; x < n; cnt++) {
        if(pre[x] == x) x = x + ck;
        else x = pre[x] + ck;
    }
    return cnt * a[ck];
}

ll solve(int len) {
    for(int x = 0, i = 1; x < n; x++) {
        if(x == s[i]) {
            pre[x] = pre[x - 1]; // 已经保证了s[1] != 0, 不会数组越界
            i++;
        }
        else pre[x] = x;
    }
    ll ans = LONG_LONG_MAX;
    for(int ck = len; ck <= k; ck++) // 因为cal中步长是ck，所以这里是调和级数求和
        ans = min(ans, cal(ck));
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    for(int i = 1; i <= m; i++)
        cin >> s[i];
    for(int i = 1; i <= k; i++)
        cin >> a[i];
    int len = check();
    if(len == -1) cout << -1;
    else cout << solve(len + 1);
}