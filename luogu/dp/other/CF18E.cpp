/**
 * @Time : 2025/1/26-3:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF18E 2000 动态规划 暴力枚举
 */
 /*
  * 上一行选择的两个字母 影响了这一行选择字母的情况
  * 所以可以暴力枚举每一行选择的前后两个字母
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 505, mod = 998244353;
int T, n, m, cost[N][26][26], infos[N][26][26][2];
string grid[N];

int cal(string& s, char c1, char c2) {
    int cnt = 0;
    for(int i = 0; i < m; i += 2) {
        if(s[i] != c1) cnt++;
        if(i + 1 < m && s[i + 1] != c2) cnt++;
    }
    return cnt;
}

void output(int c1, int c2) {
    vector<vector<char>> arr;
    for(int i = n - 1; i >= 0; i--) {
        arr.push_back({(char)(c1 + 'a'), (char)(c2 + 'a')});
        int pc1 = infos[i][c1][c2][0], pc2 = infos[i][c1][c2][1];
        c1 = pc1, c2 = pc2;
    }
    for(int i = n - 1; i >= 0; i--) {
        char t1 = arr[i][0], t2 = arr[i][1];
        for(int j = 0; j < m; j += 2) {
            cout << t1;
            if(j + 1 < m) cout << t2;
        }
        cout << "\n";
    }
}

void solve() {
    vector<vector<vector<int>>> dp(n, vector(26, vector(26, INT_MAX)));
    for(int i = 0; i < 26; i++) {
        char c1 = (char)(i + 'a');
        for(int j = 0; j < 26; j++) {
            if(i == j) continue;
            char c2 = (char)(j + 'a');
            for(int k = 0; k < n; k++)
                cost[k][i][j] = cal(grid[k], c1, c2);
            dp[0][i][j] = cost[0][i][j];
        }
    }
    for(int i = 1; i < n; i++) {
        for(int ci = 0; ci < 26; ci++) {
            for(int cj = 0; cj < 26; cj++) {
                if(ci == cj) continue;
                for(int pi = 0; pi < 26; pi++) {
                    if(pi == ci) continue;
                    for(int pj = 0; pj < 26; pj++) {
                        if(pj == cj || pj == pi) continue;
                        int temp = dp[i-1][pi][pj] + cost[i][ci][cj];
                        if(dp[i][ci][cj] > temp) {
                            dp[i][ci][cj] = temp;
                            infos[i][ci][cj][0] = pi, infos[i][ci][cj][1] = pj;
                        }
                    }
                }
            }
        }
    }
    int ans = INT_MAX, ai, aj;
    for(int ci = 0; ci < 26; ci++) {
        for(int cj = 0; cj < 26; cj++) {
            if(cj == ci) continue;
            ans = min(ans, dp[n - 1][ci][cj]);
            if(ans == dp[n - 1][ci][cj]) ai = ci, aj = cj;
        }
    }
    cout << ans << "\n";
    output(ai, aj);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        solve();
    }
};