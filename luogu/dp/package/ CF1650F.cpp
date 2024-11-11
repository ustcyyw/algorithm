/**
 * @Time : 2024/7/26-2:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1650F
 */
 /*
  * 按任务将计划分组 依次找每个任务的最快完成时间
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, a[N];
vector<int> res;
vector<vector<vector<int>>> arrs;

int min_time(vector<vector<int>>& arr) {
    int m = arr.size();
    vector<vector<int>> dp(m + 1, vector(200, (int)1e9 + 10)), infos(m + 1, vector(200, -1));
    dp[0][0] = 0;
    for(int i = 1; i <= m; i++) {
        dp[i][0] = 0;
        int time = arr[i - 1][0], p = arr[i - 1][1];
        for(int j = 1; j < 200; j++) {
            dp[i][j] = dp[i - 1][j], infos[i][j] = infos[i - 1][j];
            if(j - p >= 0 && dp[i - 1][j - p] + time < dp[i][j]) {
                dp[i][j] = dp[i - 1][j - p] + time;
                infos[i][j] = i;
            }
        }
    }
    int time = INT_MAX, j = -1;
    for(int i = 100; i < 200; i++) {
        if(dp[m][i] < time)
            time = dp[m][i], j = i;
    }
    if(time > 1e9) return -1;
    for(int i = m; i >= 1 && j > 0; i--) {
        if(infos[i][j] == infos[i - 1][j]) continue;
        res.push_back(arr[infos[i][j] - 1][2]);
        j -= arr[infos[i][j] - 1][1];
    }
    return time;
}

bool solve() {
    for(int i = 1, time = 0; i <= n; i++) {
        int t = min_time(arrs[i]);
        if(t == -1) return false;
        time += t;
        if(time > a[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        arrs.assign(n + 1, {}), res = {};
        for(int i = 1, e, t, p; i <= m; i++) {
            cin >> e >> t >> p;
            arrs[e].push_back({t, p, i});
        }
        if(!solve()) cout << "-1\n";
        else {
            cout << res.size() << "\n";
            for(int num : res)
                cout << num << " ";
            cout << "\n";
        }
    }
};