/**
 * @Time : 2023/10/19-10:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> info;

vector<int> get_info(long long num) {
    int two = 0, five = 0;
    while (num > 1 && num % 2 == 0) {
        num /= 2;
        two++;
    }
    while (num > 1 && num % 5 == 0) {
        num /= 5;
        five++;
    }
    return {two, five};
}

int solve() {
    int m = 0;
    for(auto& p : info)
        m += p[1];
    // dp[i][j][c]:截止i元素 拿了j个元素 且有c个5时，包含2的最多个数
//    vector<vector<vector<int>>> dp(n + 1, vector(k + 1, vector(m + 1, -1)));
//    dp[0][0][0] = 0;
//    for(int i = 1, total = 0; i <= n; i++) {
//        int two = info[i][0], five = info[i][1];
//        total += five;
//        dp[i][0][0] = 0;
//        for(int j = 1; j <= min(i, k); j++) {
//            for(int c = 0; c <= total; c++) {
//                dp[i][j][c] = dp[i-1][j][c];
//                if(c - five >= 0 && dp[i-1][j-1][c-five] != -1)
//                    dp[i][j][c] = max(dp[i][j][c], dp[i-1][j-1][c-five] + two);
//            }
//        }
//    }
    vector<vector<int>> dp(k + 1, vector(m + 1, -1));
    dp[0][0] = 0;
    for(int i = 1, total = 0; i <= n; i++) {
        vector<vector<int>> aux(k + 1, vector(m + 1, -1));
        aux[0][0] = 0;
        int two = info[i][0], five = info[i][1];
        total += five;
        for(int j = 1; j <= min(i, k); j++) {
            for(int c = 0; c <= total; c++) {
                aux[j][c] = dp[j][c];
                if(c - five >= 0 && dp[j-1][c-five] != -1)
                    aux[j][c] = max(aux[j][c], dp[j-1][c-five] + two);
            }
        }
        swap(aux, dp);
    }
    int res = 0;
    for(int i = 1; i <= m; i++) // 枚举5的次数
        res = max(res, min(i, dp[k][i]));
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    info.clear();
    info.push_back({0, 0}); // 哨兵
    long long num;
    for(int i = 0; i < n; i++) {
        cin >> num;
        info.push_back(get_info(num));
    }
    cout << solve() << endl;
}