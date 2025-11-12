/**
 * @Time : 2024/7/2-8:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1385D 分治 dfs
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, cnt[N][26];
string s;

int dfs(int lo, int hi, int c) {
    if(lo == hi) return s[lo] - 'a' == c ? 0 : 1;
    int mid = (lo + hi) >> 1, half = (hi - lo + 1) / 2;
    int t1 = half - (cnt[mid][c] - cnt[lo - 1][c]), t2 = half - (cnt[hi][c] - cnt[mid][c]);
    return min(t2 + dfs(lo, mid, c + 1), t1 + dfs(mid + 1, hi, c + 1));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        s = '.' + s;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 26; j++)
                cnt[i][j] = cnt[i - 1][j];
            cnt[i][s[i] - 'a']++;
        }
        cout << dfs(1, n, 0) << "\n";
    }
};