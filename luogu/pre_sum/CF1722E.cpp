/**
 * @Time : 2024/2/3-5:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

const int N = 1005;
int T, n, m;
ll nums[N][N], sum[N][N] = {0};

ll get_sum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
}

void solve() {
    for(int i = 1; i < N; i++) {
        ll line = 0;
        for(int j = 1; j < N; j++)
            line += nums[i][j], sum[i][j] = line + sum[i - 1][j];
    }
    for(int i = 1, hs, ws, hb, wb; i <= m; i++) {
        cin >> hs >> ws >> hb >> wb;
        cout << get_sum(hs + 1, ws + 1, hb - 1, wb - 1) << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        memset(nums, 0, sizeof(nums));
        for(int i = 0, h, w; i < n; i++) {
            cin >> h >> w;
            nums[h][w] += h * w;
        }
        solve();
    }
};