/**
 * @Time : 2024/12/30-10:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2045H 2200 动态规划 lcp
 */
/*
  * 从右往左考虑划分
  * dp[i][j]: 划分了s[i,n], 并且以子串s[i,j]开头的划分 最多有多少个子串
  * s[i,j]，枚举后面跟着的子串 s[j+1, k],并且要求 s[i, j] < s[j+1, k]
  * 倒着考虑的好处就是s[i, j]和要枚举的s[j+1, k]开头位置都是确定的
  * 要比较两个字符串的大小 假设lcp(t1,t2) = len
  * 那么就是两子串第len+1个字符决定其大小（len就是其中某个子串长度的话 另外一个子串更大）
  * 如果 j + 1 + len >= n || (i + len != j + 1 && s[i + len] > s[j + 1 + len])
  * 此时 s[i, j] >= s[j+1, k], 找不到合法的k满足条件
  * 解释一下条件：j + 1 + len >= n 说明s[j+1, k]整个子串是s[i,j]的前缀 s[i,j] >= s[j+1, k]
  * 否则进入到或条件第二部分 此时 j + 1 + len < n
  * i + len != j + 1 保证了s[i,j]不是s[j+1, k]的前缀
  * 两个子串互相不是前缀，那就可以比较公共前缀的后一个字母的大小来确定子串大小
  *
  * 反之s[i, j] < s[j+1,k]，其中 k = j + 1 + len
  * 而且s[j+1,k] < s[j+1, k+1]，也就是前缀相同 更长的字符串更大
  * 也就是说所有[j + 1 + len, n]上的k都能满足字典序递增的要求
  * 从这些状态都可以进行转移，那就是从一个后缀最大值转移而来即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e3 + 5;
int T, n, dp[N][N], lcp[N][N], suf[N][N][3], infos[N][N][2];
string s;

void get_lcp() {
    for (int j = n - 1; j >= 0; j--) {
        for (int i = j; i >= 0; i--) {
            if (s[i] != s[j]) continue;
            if (i != n - 1 && j != n - 1)
                lcp[i][j] = 1 + lcp[i + 1][j + 1];
            else lcp[i][j] = 1;
        }
    }
}

void solve() {
    get_lcp();
    for(int i = n - 1; i >= 0; i--) {
        for(int j = n - 1; j >= i; j--) {
            int len = j + 1 < n ? lcp[i][j + 1] : N;
            len = min(len, j - i + 1); // lcp数组算的是原字符串的后缀串 这里算的s[i,j]和s[j+1,n-1]
            int k = j + 1 + len;
            // s[i, j] >= s[j+1, k]的情况
            if(k >= n || (i + len != j + 1 && s[i + len] > s[k])) {
                dp[i][j] = j == n - 1 ? 1 : -1;
                infos[i][j][0] = infos[i][j][1] = -1;
            } else {
                dp[i][j] = suf[j + 1][k][2] + 1;
                infos[i][j][0] = suf[j + 1][k][0], infos[i][j][1] = suf[j + 1][k][1];
            }
            suf[i][j][0] = i, suf[i][j][1] = j, suf[i][j][2] = dp[i][j];
            if(j + 1 < n && suf[i][j][2] < suf[i][j + 1][2]) {
                suf[i][j][1] = suf[i][j + 1][1];
                suf[i][j][2] = suf[i][j + 1][2];
            }
        }
    }
    int cnt = 0, i = 0, j;
    for(int jt = 0; jt < n; jt++) {
        if(dp[0][jt] > cnt)
            cnt = dp[0][jt], j = jt;
    }
    cout << cnt << "\n";
    while(i != -1) {
        cout << s.substr(i, j - i + 1) << "\n";
        int it = infos[i][j][0], jt = infos[i][j][1];
        i = it, j = jt;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s;
        n = s.size();
        solve();
    }
};