/**
 * @Time : 2025/2/23-5:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF792C 2000 动态规划 刷表
 */
/*
  * dp[i][j]: 截止i元素 数位和对3取余的结果为j的最小删除次数
  * 当前元素可以删 也可以不删
  * infos[i][j]: 记录状态转移
  *
  * 注意 如果答案长度大于1 0不可以作为最终答案的开头数字
  * 答案长度为1，并且是单个0的情况合法 但是既然答案长度为1
  * 在找不到其它可能的答案的情况下 再去s中找是否有0存在就能解决这种特殊情况
  *
  * 所以在状态转移的时候 s[i]如果非0 一种可能的情况可以是把s[0,i-1]都删掉
  * 将这个位置作为答案的起点 设置infos[i][cj] = -1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
ll n;
vector<vector<int>> dp, infos;
string s, ans;

void solve() {
    for(int i = 0; i < n; i++) {
        // 考虑当前元素做第一个元素
        int cj = (s[i] - '0') % 3, nj = (s[i + 1] - '0') % 3;
        if(s[i] != '0' && dp[i][cj] > i)
            dp[i][cj] = i, infos[i][cj] = -1;
        if(i + 1 < n) {
            // 下一个元素删掉
            for(int j = 0; j < 3; j++)
                dp[i + 1][j] = dp[i][j] + 1, infos[i + 1][j] = j;
            // 下一个元素不删掉
            for(int j = 0; j < 3; j++) {
                int tj = (nj + j) % 3;
                if(dp[i + 1][tj] > dp[i][j])
                    dp[i + 1][tj] = dp[i][j], infos[i + 1][tj] = j;
            }
        }
    }
    if(dp[n - 1][0] >= N) {
        if(s.find("0") != string::npos) cout << "0";
        else cout << "-1";
        return;
    }
    for(int i = n - 1, j = 0; i >= 0 && j != -1; i--) {
        int pj = infos[i][j];
        // 还原字符串 前后两个状态的删除次数一致 或者 当前字符就是起点 说明不需要删除当前字符
        if(pj == -1 || dp[i - 1][pj] == dp[i][j])
            ans.push_back(s[i]);
        j = pj;
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> s;
    n = s.size();
    dp.assign(n, vector(3, N)), infos.assign(n, vector(3, -1));
    solve();
};