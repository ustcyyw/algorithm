/**
 * @Time : 2024/12/1-11:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1996C 1200 前缀和
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
ll T, n, q;
string a, b;
vector<vector<int>> cnt1, cnt2;

vector<vector<int>> get_cnt(string s) {
    vector<vector<int>> cnt(n + 1, vector(26, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 26; j++)
            cnt[i][j] = cnt[i - 1][j];
        cnt[i][s[i] - 'a']++;
    }
    return cnt;
}

void solve(int l, int r) {
    int ans = 0;
    for(int j = 0; j < 26; j++) {
        int c1 = cnt1[r][j] - cnt1[l - 1][j], c2 = cnt2[r][j] - cnt2[l - 1][j];
        ans += max(0, c1 - c2);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> q >> a >> b;
        cnt1 = get_cnt('.' + a), cnt2 = get_cnt('.' + b);
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            solve(l, r);
        }
    };
};