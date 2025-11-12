/**
 * @Time : 2024/1/22-10:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int MIN = -1e9;
int n, total, vMax;
vector<vector<int>> arr;
// 确定了要多少个桶 贪心 先选择最大容量的桶
int count() {
    int l = n - 1, sum = 0;
    while(l >= 0 && sum < total)
        sum += arr[l--][1];
    int cnt = n - 1 - l;
    return cnt;
}
// dp[i][j][v]: 截止第i个位置，选取了j个桶 总容量为v的最大现有水量 0-1背包问题 滚动优化。
// 在满足总容量 >= total且选取的容器数量为cnt的前提下
// 求出已有的最大水量mv 还需要转移的水量(花费的时间)就是total - mv
void solve() {
    int cnt = count();
    vector<vector<int>> dp(cnt + 1, vector(vMax + 1, MIN)), pre(cnt + 1, vector(vMax + 1, MIN));
    pre[0][0] = 0, dp[0][0] = 0;
    for(int i = 0, sum = 0; i < n; i++) {
        int a = arr[i][0], b = arr[i][1];
        sum += b;
        for(int j = 1; j <= min(cnt, i + 1); j++) {
            for(int v = sum; v >= 0; v--) {
                if(v - b >= 0) dp[j][v] = max(pre[j][v], pre[j - 1][v - b] + a);
                else dp[j][v] = pre[j][v];
            }
        }
        swap(dp, pre);
    }
    int res = INT_MAX;
    for(int i = total; i <= vMax; i++)
        res = min(res, total - pre[cnt][i]);
    cout << cnt << " " << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    arr = vector(n, vector(2, 0)), total = 0, vMax = 0;
    for(int i = 0, a; i < n; i++) {
        cin >> a;
        total += a, arr[i][0] = a;
    }
    for(int i = 0, b; i < n; i++) {
        cin >> b;
        vMax += b, arr[i][1] = b;
    }
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    solve();
}