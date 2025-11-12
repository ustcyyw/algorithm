/**
 * @Time : 2024/6/20-11:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1296E2 思维 + 线性动态规划
 */
/*
 * 字符交换为有序 本质上就是冒泡排序 要使最终字符串有序
 * 每一个逆序对都需要进行交换 那么他们颜色不同
 *
 * 对于一个下降子序列 s[i1], s[i2], s[i3]...s[im]
 * i1的颜色和i2,i3...im不同 这样才能让他们交换到前面 假设i1的颜色是1
 * 那么i2,i3,...im的颜色 > 1。
 * i2的颜色和i3,...im不同 这样才能让他们交换到前面 i2的颜色 > 1 假设是2
 * 那么i3..im的颜色 > 2
 * ... 以此类推 下降子序列的长度是多少 这个序列的颜色就得是多少。
 * 因此 找到最长下降子序列 其长度为cnt，那么整个字符串染色数至少为cnt。
 *
 * 接下来证明 假设dp[i]是以i为结尾的下降子序列最大长度 那么就用dp[i]的值进行染色 是一种可行方案
 * 这种方案的染色数目是cnt 已经说明了染色数目不能小于cnt 因此方案可行就是最终答案
 * 考虑dp[i]的转移方程 dp[i] = max{dp[j] + 1, for j < i and s[j] > s[i]}
 * 也就是说i位置的颜色值dp[i] 大于其左边任意比他大的字符的颜色值dp[j]
 * （大于其左边与其构成逆序对的位置的颜色）
 * 那么i就可以交换到正确的位置 因此这个方案可行
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, T = 1e4;
typedef long long ll;
int n, ans[26], pre[N], dp[N];
string s;

void solve() {
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        int c = s[i] - 'a';
        if(c == 25) dp[i] = 1;
        for(int j = c + 1; j < 26; j++)
            dp[i] = max(dp[i], dp[pre[j]] + 1);
        cnt = max(dp[i], cnt);
        pre[c] = i;
    }
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++)
        cout << dp[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    s = '.' + s;
    solve();
};