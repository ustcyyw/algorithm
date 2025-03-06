/**
 * @Time : 2025/3/5-8:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF846D 1900 二分答案 前缀和
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, P = 13331;
ll n, m, k, q;
vector<vector<int>> pos;

ll sumOf(vector<vector<int>>& preSum, int x1, int y1, int x2, int y2){
    return preSum[x2][y2] - preSum[x1 - 1][y2] - preSum[x2][y1 - 1] + preSum[x1 - 1][y1 - 1];
}
// 会坏返回true
bool check(int idx) {
    vector<vector<int>> nums(n + 1, vector(m + 1, 0));
    for(int i = 0; i <= idx; i++) {
        int x = pos[i][1], y = pos[i][2];
        nums[x][y] = 1;
    }
    for(int i = 1; i <= n; i++){
        int lineSum = 0;
        for(int j = 1; j <= m; j++){
            lineSum += nums[i][j];
            nums[i][j] = nums[i - 1][j] + lineSum;
        }
    }
    for(int i = 1; i + k - 1 <= n; i++) {
        for(int j = 1; j + k - 1 <= m; j++)
            if(sumOf(nums, i, j, i + k - 1, j + k - 1) == k * k)
                return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k >> q;
    for(int i = 1, x, y, t; i <= q; i++) {
        cin >> x >> y >> t;
        pos.push_back({t, x, y});
    }
    sort(pos.begin(), pos.end());
    int lo = 0, hi = q;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << (lo == q ? -1 : pos[lo][0]) << "\n";
}