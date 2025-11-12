/**
 * @Time : 2025/3/3-10:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF825F 2400 动态规划 字符串双hash 调和级数
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 8000 + 5, P = 13331;
int n, c[N];
string s;
const ull B1 = 131, P1 = 1e9 + 7;      // 第一个哈希参数
const ull B2 = 29, P2 = 998244353;  // 第二个哈希参数

ull H1[N], H2[N];  // 哈希值
ull P1_pow[N], P2_pow[N];  // 幂次表

void init_hash() {
    P1_pow[0] = P2_pow[0] = 1;
    for (int i = 1; i <= n; i++) {
        P1_pow[i] = P1_pow[i - 1] * B1 % P1;
        P2_pow[i] = P2_pow[i - 1] * B2 % P2;
    }
    for (int i = 1; i <= n; i++) {
        H1[i] = (H1[i - 1] * B1 + s[i]) % P1;
        H2[i] = (H2[i - 1] * B2 + s[i]) % P2;
    }
}

// 获取子串 [l, r] 的哈希值
pair<ull, ull> get_hash(int l, int r) {
    ull hash1 = (H1[r] - H1[l - 1] * P1_pow[r - l + 1] % P1 + P1) % P1;
    ull hash2 = (H2[r] - H2[l - 1] * P2_pow[r - l + 1] % P2 + P2) % P2;
    return {hash1, hash2};
}

int cal_digit(int x)
{
    int res = 0;
    while(x) x /= 10, ++res;
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    n = s.size();
    for(int i = 1; i <= n; i++)
        c[i] = cal_digit(i);
    s = '.' + s;
    init_hash();
    // cnt[i][j] : s[i,j]为重复子串，其前置位置重复了多处次
    vector<vector<int>> cnt(n + 1, vector(n + 1, 0));
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;
    for(int j = 1; j <= n; j++) {
        for(int i = j; i > 0; i--) {
            int len = j - i + 1, k = i - len;
            if(k > 0 && get_hash(k, i - 1) == get_hash(i, j))
                cnt[i][j] = cnt[k][i - 1] + 1;
            else cnt[i][j] = 1;
            // 这里是调和级数求和 最坏的情况下 可以将s[i,j]一直向前匹配到字符串开头
            // 那么对于确定的i, 计算次数是 j / len
            // 外层对i的枚举，等价于 len 从1到j枚举，那么求和的总计算次数就是 log(j) * j
            for(int t = 1; t <= cnt[i][j]; t++)
                dp[j] = min(dp[j], dp[j - t * len] + c[t] + len);
        }
    }
    cout << dp[n];
}