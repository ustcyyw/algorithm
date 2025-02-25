/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 5, M = 400;
int n, k, dp[N][2 * N], infos[N][2 * N];
string s;

string solve() {
    dp[0][k] = 1;
    for(int i = 1; i <= n; i++) {
        char c = s[i];
        int up = i == n ? 2 * k : 2 * k - 1, down = i == n ? 0 : 1;
        for(int j = down; j <= up; j++) {
            if((c == 'L' || c == '?') && j - 1 >= 0 && dp[i - 1][j - 1])
                dp[i][j] = 1, infos[i][j] = j - 1;
            if((c == 'W' || c == '?') && dp[i - 1][j + 1])
                dp[i][j] = 1, infos[i][j] = j + 1;
            if((c == 'D' || c == '?') && dp[i - 1][j])
                dp[i][j] = 1, infos[i][j] = j;
        }
    }
    if(!dp[n][2 * k] && ! dp[n][0]) return "NO";
    int ck = dp[n][2 * k] ? 2 * k : 0;
    for(int i = n; i >= 1; i--) {
        int pk = infos[i][ck];
        if(ck > pk) s[i] = 'L';
        else if(ck < pk) s[i] = 'W';
        else s[i] = 'D';
        ck = pk;
    }
    return s.substr(1);
}

int main() {
    cin >> n >> k >> s;
    s = '.' + s;
    cout << solve() << "\n";
}