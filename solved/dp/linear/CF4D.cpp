/**
 * @Time : 2025/1/22-11:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF4D 1700 动态规划 线性动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 3e5 + 5, mod = 998244353;
int T, n, w, h;
vector<vector<int>> arr;

void solve() {
    if(arr.empty()) {
        cout << "0";
        return ;
    }
    n = arr.size();
    int ans = 1, idx = 0;
    vector<int> dp(n, 1), infos(n, -1);
    for(int i = 1; i < n; i++) {
        for(int j = i - 1; j >= 0; j--) {
            if(arr[i][0] > arr[j][0] && arr[i][1] > arr[j][1] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                infos[i] = j;
            }
        }
        ans = max(ans, dp[i]);
        if(dp[i] == ans) idx = i;
    }
    cout << ans << "\n";
    vector<int> aux;
    while(idx != -1) {
        aux.push_back(arr[idx][2]);
        idx = infos[idx];
    }
    reverse(aux.begin(), aux.end());
    for(int num : aux)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> w >> h;
        for(int i = 1, cw, ch; i <= n; i++) {
            cin >> cw >> ch;
            if(cw > w && ch > h) arr.push_back({cw, ch, i});
        }
        sort(arr.begin(), arr.end());
        solve();
    }
};