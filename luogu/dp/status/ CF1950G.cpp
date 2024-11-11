/**
 * @Time : 2024/3/29-4:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * n = 16 状态压缩
  * 因为歌曲的连接有要求 所以当前歌曲和上个结尾的歌曲有关 像旅行商问题
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, M = 13 * 9;
int T, n, valid[16][16] = {0};
string g[17], w[17];

int solve() {
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++)
            valid[i][j] = valid[j][i] = g[i] == g[j] || w[i] == w[j];
    }
    int u = (1 << n) - 1, ans = 1;
    vector<vector<int>> cache(u + 1, vector(n, 0));
    for(int i = 0; i < n; i++)
        cache[1 << i][i] = 1;
    function<int(int, int)> dfs = [&](int s, int i) -> int {
        if(cache[s][i] != 0) return cache[s][i];
        int flag = -1, mask_i = 1 << i;
        for(int j = 0; j < n; j++) { // 枚举上一个曲子
            if(((1 << j) & s) && valid[i][j] && dfs(s ^ mask_i, j) == 1) {
                flag = 1;
                break;
            }
        }
        if(flag == 1) ans = max(ans, __builtin_popcount(s));
        cache[s][i] = flag;
        return flag;
    };
    for(int s = 1; s <= u; s++) {
        for(int i = 0; i < n; i++) {
            if((1 << i) & s) dfs(s, i);
        }
    }
    return n - ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> g[i] >> w[i];
        cout << solve() << "\n";
    }
};