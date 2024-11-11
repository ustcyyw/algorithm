/**
 * @Time : 2024/1/16-2:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/* 字符串s确定移动顺序 每次移动都是两个字母的距离
 *
 * m <= 20 并且距离与排列顺序有关 排列型状态压缩
 * 假设有某个状态s，t = bit_count(s)
 * 用状态表示已经排列了的t个字母，并且当前要选择一个不在s中的字母放在位置t
 * 转移方程一般是 dp[s | (1 << j)] = min{dp[s] + cost(j), j 不在s中}
 * 距离和放置的位置有关 但是s中无法得出放置的位置
 * 我们要设计一种无后效性的dp：每一次装一个字母就直接统计出来它的所有贡献（费用提前思想）
 * 因此 cost(j) 表示的在t位置放置字母j 对距离总和的影响
 *
 * 在s中的字母 都是排在j之前的 记为x： dis1 = sum{cnt[x][j] * (pos[j] - pos[x])}
 * 不在s中的字母 都是排在j之后的 记y： dis2 = sum{cnt[y][j] * (pos[y] - pos[j])}
 * t = pos[j]是确定值 因此单独抽取出来
 * sum{t * cnt[x][j], x in s} - sum{t * cnt[y][j], y not in s}
 * = t * (sum{cnt[x][j], x in s} - sum{cnt[y][j], y not in s})
 * 这两项就是j对距离总和的贡献
 *
 * 而dis1中的 -sum{cnt[x][j] * pos[x]} 在前面放在x的时候就已经计算过了
 * 因为在放置x的时候j相当于后置字母 会有一项 -cnt[j][x] * pos[x], 而cnt[x][j] = cnt[j][x]
 * 同理 dis2中 sum{cnt[y][j] * pos[y]} 也会在后面放置y的时候计算 （所以才叫费用提前思想）
 * 所以 总距离的计算是正确的
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, U = (1 << 20) + 5;
int n, m, cnt[20][20], u;
long long dp[U];
string line;

void init() {
    for (int i = 0; i < m; i++)
        memset(cnt[i], 0, sizeof(cnt[i]));
    for (int i = 1; i < n; i++) {
        int c1 = line[i - 1] - 'a', c2 = line[i] - 'a';
        if(c1 == c2) continue; // 前后两个字符相等 移动距离为0
        cnt[c1][c2]++, cnt[c2][c1]++;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    u = (1 << m) - 1;
    cin >> line;
    init();
    fill(dp, dp + u + 1, LONG_LONG_MAX);
    dp[0] = 0;
    for(int s = 0; s < u; s++) {
        int t = __builtin_popcount(s); // 当前字母放置的位置是t
        for(int j = 0; j < m; j++) {
            if((1 << j) & s) continue; // j字母已经被分配了
            int next = s | (1 << j);
            long long x = 0, y = 0;
            // 计算cost[j]的两项
            for(int k = 0; k < m; k++) {
                if((1 << k) & s) x += cnt[k][j];
                else y += cnt[j][k];
            }
            dp[next] = min(dp[next], dp[s] + (x - y) * t);
        }
    }
    cout << dp[u] << endl;
}