/**
 * @Time : 2023/12/8-2:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 用range[i] 表示以i为起点的按列递增的序列最大长度
 * 多个列中取最大
 * 如果某一列上 col[lo, hi]是递增的，那么col[lo + 1, hi], col[lo + 2, hi]...col[hi, hi]也是递增的
 * 因此双指针找到某列某点开始的最长递增序列，可以将该序列中每个位置的信息都进行更新
 */

#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int n, m, k, range[N];

void init(vector<vector<int>>& grid) {
    memset(range, 0, sizeof(range));
    for(int i = 1; i <= m; i++) {
        for(int lo = 1, hi = 1; hi <= n; ) {
            hi = lo + 1;
            while(hi <= n && grid[hi][i] >= grid[hi - 1][i])
                hi++;
            while(lo < hi) { // 更新这个递增序列中每个点的信息
                range[lo] = max(range[lo], hi - lo);
                lo++;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    vector<vector<int>> grid(n + 1, vector(m + 1, 0));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }
    init(grid);
    cin >> k;
    for(int i = 1, l, r; i <= k; i++) {
        cin >> l >> r;
        if(range[l] >= r - l + 1) cout << "Yes\n";
        else cout << "No\n";
    }
}