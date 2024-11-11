/**
 * @Time : 2023/8/23-12:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 11, M = 1005;
int n, m, k, sum[N][M] = {0};
// 左上角坐标 x1,y1; 右下角坐标 x2,y2
int range_sum(int x1, int y1, int x2, int y2){
    return sum[x2 + 1][y2 + 1] - sum[x1][y2 + 1] - sum[x2 + 1][y1] + sum[x1][y1];
}
// status中的某一位为1，就表示在这一行与下一行之间切一刀。 status的最高位为 n - 1
int count(int status) {
    vector<int> rows = {-1};
    for(int i = 0; i < n - 1; i++) {
        if((1 << i) & status)
            rows.push_back(i);
    }
    rows.push_back(n - 1); // 最后一行后面默认边界
    function<bool(int, int)> check = [&](int y1, int y2) -> bool {
        for(int i = 0; i < rows.size() - 1; i++) {
            int x1 = rows[i] + 1, x2 = rows[i + 1];
            if(range_sum(x1, y1, x2, y2) > k) return false;
        }
        return true;
    };
    int res = __builtin_popcount(status);
    for(int i = 0, pre = -1; i < m; ) {
        while (i < m && check(pre + 1, i)) i++;
        if(pre + 1 == i) return -1;
        else if(i != m) res++, pre = i - 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k;
    string line;
    for(int i = 1; i <= n; i++) {
        cin >> line;
        for(int j = 1, t = 0; j <= m; j++) {
            t += line[j - 1] - '0';
            sum[i][j] = sum[i - 1][j] + t;
        }
    }
    if(sum[n][m] <= k) { // 一刀都不用切的情况
        cout << 0 << endl;
        return 0;
    }
    int res = INT_MAX, u = (1 << (n - 1)) - 1;
    for(int s = u; s; s = (s - 1) & u) {
        int t = count(s);
        if(t != -1) res = min(res, t);
    }
    cout << res << endl;
}