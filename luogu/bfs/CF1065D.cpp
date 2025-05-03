/**
 * @Time : 2025/4/30-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1065D 2200 bfs
 */
 /*
  * 在这个题中 涉及到的状态有 位置 x,y 有已经按顺序走过了k序号，以及当前是什么棋子s
  * 因此可以用(x,y,k,s)来表示一个"位置" 要求到达最终"位置"的最短路径
  * 因为耗时都是1s，所以就是bfs
  * 在bfs的时候要注意，能切换棋子，能进行位移动，并且只保留切换次数最少的方式
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e2+ 5, mod = 998244353;
ll T, n, a, b, c, d, t1 = 1e9, t2 = 1e6, t3 = 1e3;
int grid[N][N], infos[N][N][N][3][2];
vector<vector<int>> dire0 = {{0,1},{0,-1},{1,0},{-1,0}};
vector<vector<int>> dire1 = {{1,1},{-1,-1},{1,-1},{-1,1}};
vector<vector<int>> dire2 = {{1,2},{1,-2},{2,1},{2,-1},{-1,2},{-1,-2},{-2,1},{-2,-1}};

ll get_key(int x, int y, int k, int s) {
    return x * t1 + y * t2 + k * t3 + s;
}

void get_status(ll key, int& x, int& y, int& k, int& s) {
    s = key % 1000;
    key /= 1000, k = key % 1000;
    key /= 1000, y = key % 1000;
    key /= 1000, x = key % 1000;
}

bool add(set<ll> &set, int x, int y, int k, int s, int step, int cnt) {
    if(grid[x][y] == k + 1) k++; // 已经走过了序号k，并且现在到了k+1序号的位置，那么序号+1
    int ps = infos[x][y][k][s][0];
    // 满足没有到达过这个"位置" 或者到达这个位置 使用的切换状态次数最少
    if(ps == 0 || (ps == step && infos[x][y][k][s][1] > cnt)) {
        infos[x][y][k][s][0] = step, infos[x][y][k][s][1] = cnt;
        set.insert(get_key(x, y, k, s));
    }
    return k == n * n;
}
// 切换棋子的种类
void change_status(set<ll>& st, int x, int y, int k, int s, int step, int cnt) {
    for(int i = 0; i < 3; i++) {
        if(i == s) continue;
        add(st, x, y, k, i, step + 1, cnt + 1);
    }
}

void move(set<ll>& st, vector<vector<int>>& dires,
          int x, int y, int k, int s, int step, int cnt) {
    change_status(st, x, y, k, s, step, cnt);
    for(vector<int>& dire : dires) {
        int dx = dire[0], dy = dire[1];
        int tx = x, ty = y;
        while(true) {
            tx += dx, ty += dy;
            if(tx < 1 || ty < 1 || tx > n || ty > n) break;
            add(st, tx, ty, k, s, step + 1, cnt);
        }
    }
}

void move_horse(set<ll>& st, vector<vector<int>>& dires,
                int x, int y, int k, int s, int step, int cnt) {
    change_status(st, x, y, k, s, step, cnt);
    for(vector<int>& dire : dires) {
        int nx = x + dire[0], ny = y + dire[1];
        if(nx < 1 || ny < 1 || nx > n || ny > n) continue;
        add(st, nx, ny, k, s, step + 1, cnt);
    }
}

void bfs() {
    set<ll> st;
    add(st, a, b, 0, 0, 1, 0); // 为了区别未访问，将初始的step设置为1，最后答案要减去1
    add(st, a, b, 0, 1, 1, 0);
    add(st, a, b, 0, 2, 1, 0);
    while(true) {
        set<ll> cur;
        for(ll key : st) {
            int x, y, k, s;
            get_status(key, x, y, k, s);
            int step = infos[x][y][k][s][0], cnt = infos[x][y][k][s][1];
            if(s == 0) move(cur, dire0, x, y, k, s, step, cnt);
            else if(s == 1) move(cur, dire1, x, y, k, s, step, cnt);
            else move_horse(cur, dire2, x, y, k, s, step, cnt);
        }
        if(infos[c][d][n * n][0][0] != 0 || infos[c][d][n * n][1][0] != 0 ||
           infos[c][d][n * n][2][0] != 0)
            break;
        swap(cur, st);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 1) a = i, b = j;
            if(grid[i][j] == n * n) c = i, d = j;
        }
    }
    bfs();
    int step = INT_MAX, cnt = -1;
    for(int s = 0; s < 3; s++) {
        int st = infos[c][d][n * n][s][0], ct = infos[c][d][n * n][s][1];
        if(st != 0 && (st < step || (st == step && ct < cnt)))
            step = st, cnt = ct;
    }
    cout << step - 1 << " " << cnt << "\n";
}