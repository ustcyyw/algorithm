/**
 * @Time : 2024/12/26-11:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1807F 1700 模拟
 */
 /*
  * 模拟 计算运动后的位置及方向的改变
  * 还需要判断是否经过了终点
  *
  * 除了计算运动步数（走多少次会碰壁外） 将水平和竖直方向的运行拆分开来考虑比较简单
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, sx, sy, tx, ty;
string dire;

bool check(char c1, char c2, int nx, int ny) {
    if(abs(tx - sx) != abs(ty - sy)) return false;
    bool f1, f2;
    if(c1 == 'U') f1 = nx <= tx && sx >= tx;
    else f1 = nx >= tx && sx <= tx;
    if(c2 == 'L') f2 = ny <= ty && sy >= ty;
    else f2 = ny >= ty && sy <= ty;
    return f1 && f2;
}

bool change() {
    char c1 = dire[0], c2 = dire[1];
    int d1 = c1 == 'U' ? sx - 1 : n - sx;
    int d2 = c2 == 'L' ? sy - 1 : m - sy;
    int d = min(d1, d2);
    int nx = c1 == 'U' ? sx - d : sx + d;
    int ny = c2 == 'L' ? sy - d : sy + d;
    char nc1 = c1, nc2 = c2;
    if(c1 == 'U' && nx == 1) nc1 = 'D';
    if(c1 == 'D' && nx == n) nc1 = 'U';
    if(c2 == 'L' && ny == 1) nc2 = 'R';
    if(c2 == 'R' && ny == m) nc2 = 'L';
    // 判断是否经过了终点
    if(check(c1, c2, nx, ny)) return true;
    sx = nx, sy = ny, dire[0] = nc1, dire[1] = nc2;
    return false;
}

int solve() {
    unordered_set<string> marked;
    int step = 0;
    while(true) {
        string key = dire + to_string(sx) + "，" +to_string(sy);
        if(marked.count(key)) return -1;
        marked.insert(key);
        if(change()) return step;
        step++;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> m >> sx >> sy >> tx >> ty >> dire;
        cout << solve() << "\n";
    }
};