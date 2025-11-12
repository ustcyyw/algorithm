/**
 * @Time : 2024/9/6-5:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1840F
 */
 /*
  * 子弹数量r <= 100 打穿整个坐标
在第t秒 有子弹射中i坐标 人如果在i位置 那么他只有一个方向可走 i+1
如果此时也有子弹射中i+1 那就死定了
可以通过等待来躲避子弹 总共100颗子弹 等待最多110秒或许就够了
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e5 + 5, mod = 1e9 + 7;
int T, n, m, r, mt = 105;
map<int, set<int>> shot;
vector<vector<vector<bool>>> marked;

void check_add(queue<vector<int>>& queue, int x, int y, int stay) {
    int time = x + y + stay;
    if(x > n || y > m || stay == mt || marked[x][y][stay]) return ;
    if(shot[time].count(x) || shot[time].count(y + N)) return;
    queue.push({x, y, stay}), marked[x][y][stay] = true;
}


int solve() {
    marked.assign(n + 1, vector(m + 1, vector(105, false)));
    queue<vector<int>> queue;
    queue.push({0, 0, 0}), marked[0][0][0] = true;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            vector<int>& pos = queue.front();
            if(pos[0] == n && pos[1] == m) return pos[0] + pos[1] + pos[2];
            for(int i = 0; i < 3; i++) {
                pos[i]++;
                check_add(queue, pos[0], pos[1], pos[2]);
                pos[i]--;
            }
            queue.pop();
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> r;
        shot = {};
        for(int i = 1, t, d, coord; i <= r; i++) {
            cin >> t >> d >> coord;
            int key = d == 2 ? coord + N : coord;
            shot[t].insert(key);
        }
        cout << solve() << "\n";
    }
};