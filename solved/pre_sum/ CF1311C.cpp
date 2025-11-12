/**
 * @Time : 2024/6/24-11:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1311C 前缀和
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m, sum[N][26];
string s;

void solve() {
    int cnt[26] = {0};
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 26; j++)
            sum[i][j] = sum[i - 1][j];
        sum[i][s[i] - 'a']++;
        cnt[s[i] - 'a']++;
    }
    for(int i = 1, p; i <= m; i++) {
        cin >> p;
        for(int j = 0; j < 26; j++)
            cnt[j] += sum[p][j];
    }
    for(int j = 0; j < 26; j++)
        cout << cnt[j] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> s;
        s = '.' + s;
        solve();
    }
};