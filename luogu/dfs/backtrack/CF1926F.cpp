/**
 * @Time : 2024/12/11-2:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1926F 2200 思维 dfs 回溯
 */
/*
  * 关键1：能凑出四个角的黑色格子 集中在中心的边长为5的正方形内
  * 关键2：只要将中心边长为3的正方形的边（8个格子）都变白
  * 就一定能保证1中所说的所有黑色格子至少有一个角变白 因此最多修改8个格子即可
  * 关键3：中心格子和四个角的格子坐标和奇偶性相同（变化时坐标和分别变了-2，0，0，2）
  * 奇偶坐标的格子相互不影响对角线四个角 因此可以将格子按奇偶分开计算
  * 分别保证同一类格子满足要求即可 每类格子最多修改4个即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, dx[4] = {1,1,-1,-1}, dy[4] = {-1,1,1,-1}, ans[2];
string grid[7];
vector<vector<int>> pos1, pos2;

int init = []() -> int {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++){
            if((i + j) % 2 == 1) pos1.push_back({i, j});
            else pos2.push_back({i, j});
        }
    }
    return 0;
}();

// flag 标识检查的坐标是奇数还是偶数
bool check(int flag) {
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            if((i + j) % 2 != flag || grid[i][j] != 'B') continue;
            int cnt = 0;
            for(int k = 0; k < 4; k++) {
                int nx = i + dx[k], ny = j + dy[k];
                cnt += grid[nx][ny] == 'B';
            }
            if(cnt == 4) return false;
        }
    }
    return true;
}

void dfs(vector<vector<int>>& pos, int flag, int i, int cnt) {
    if(check(flag)) {
        ans[flag] = min(ans[flag], cnt);
        return;
    }
    if(cnt >= ans[flag]) return;
    for(int j = i; j < pos.size(); j++) {
        int x = pos[j][0], y = pos[j][1];
        if(grid[x][y] == 'B') {
            grid[x][y] = 'W';
            dfs(pos, flag, j + 1, cnt + 1);
            grid[x][y] = 'B';
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        ans[0] = ans[1] = 4;
        for(int i = 0; i < 7; i++)
            cin >> grid[i];
        dfs(pos1, 1, 0, 0);
        dfs(pos2, 0, 0, 0);
        cout << (ans[0] + ans[1]) << "\n";
    }
};