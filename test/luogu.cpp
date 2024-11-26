/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, ans[N][2];
map<int, vector<vector<int>>> mp;

int cal(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
        return a[5] == b[5] ? a[4] < b[4] : a[5] < b[5];
    });
    int cnt = 0, sz = arr.size();
    for(int i = 0, j; i < sz; ) {
        j = i, cnt++;
        int hi = arr[i][5];
        while(j < sz && arr[j][4] <= hi) {
            int idx = arr[j][0], a = arr[j][1], m = arr[j][3];
            int am = a - hi, bm = m - am;
            ans[idx][0] = am, ans[idx][1] = bm;
            j++;
        }
        i = j;
    }
    return cnt;
}

void solve() {
    int cnt = 0;
    for(auto& p : mp)
        cnt += cal(p.second);
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++)
        cout << ans[i][0] << " " << ans[i][1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        mp = {};
        for(int i = 1, a, b, m; i <= n; i++) {
            cin >> a >> b >> m;
            int l = max(0, a - m), r = a - m + min(b, m);
            mp[a + b - m].push_back({i, a, b, m, l, r});
        }
        solve();
    };
};