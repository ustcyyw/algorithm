/**
 * @Time : 2023/10/19-9:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 3005;
int H, W, T, grid[N][N], sum[N][N];

void pre_sum() {
    for(int i = 1; i <= H; i++) {
        for(int j = 1, line = 0; j <= W; j++) {
            line += grid[i - 1][j - 1];
            sum[i][j] = line + sum[i - 1][j];
        }
    }
}

int get_sum(int x1, int y1, int x2, int y2) {
    return sum[x2 + 1][y2 + 1] - sum[x2 + 1][y1] - sum[x1][y2 + 1] + sum[x1][y1];
}

long long solve() {
    pre_sum();
    long long res = 0;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(grid[i][j]) continue;
            int lo = 0, hi = min(H - i - 1, W - j - 1);
            while (lo < hi) {
                int mid = (lo + hi + 1) >> 1;
                if(get_sum(i, j, i + mid, j + mid) == 0) lo = mid;
                else hi = mid - 1;
            }
            res += lo + 1;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> H >> W >> T;
    for(int t = 0, i, j; t < T; t++) {
        cin >> i >> j;
        grid[i - 1][j - 1] = 1;
    }
    cout << solve() << endl;
}