/**
 * @Time : 2024/11/15-11:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF978D 暴力枚举 模拟 1500
 */
 /*
  * 第一个元素和第二个元素 分别有9种可能的操作情况
  * 直接枚举 就能确定公差d 然后逐个判断即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, b[N], add[3] = {-1, 0, 1};

int cal(int b1, int b2) {
    int d = b2 - b1, cnt = 0;
    for(int i = 3, pre = b2; i <= n; i++, pre += d) {
        int diff = abs(b[i] - pre - d);
        if(diff > 1) return 1e9;
        cnt += diff;
    }
    return cnt;
}

int solve() {
    if(n <= 2) return 0;
    int ans = 1e9;
    for(int a1 : add) {
        int b1 = b[1] + a1;
        for(int a2 : add) {
            int b2 = b[2] + a2, base = abs(a1) + abs(a2);
            ans = min(ans, base + cal(b1, b2));
        }
    }
    return ans >= 1e9 ? -1 : ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    cout << solve();
};