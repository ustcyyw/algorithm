/**
 * @Time : 2023/11/25-7:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 假设在第一行已经不能再进行操作的情况下 现在能影响第一行的 就只有第二行
 * 如果在第y列 第一行是0 那么当前位置就必须按一下 以保证第一行该列变为1
 * 将5个位置检查之后 第二行也不能再改变
 * 同理 检查第三行、第四行、第五行 然后观察是否全变为1
 *
 * 但是不知道第一行的初始状态是多少 可以枚举第一行的操作方案
 * 对于每一个操作方案 求出是否在6步内完成 并且取其中的最少步骤
 */
#include<bits/stdc++.h>
using namespace std;

const int target = (1 << 25) - 1;
const int dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};

void change(int x, int y, int& s){
    s ^= 1 << (x * 5 + y);
    for(int k = 0; k < 4; k++) {
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || ny < 0 || nx >= 5 || ny >= 5) continue;
        s ^= 1 << (nx * 5 + ny);
    }
}

int solve2(int s, int cnt) {
    for(int x = 1; x < 5; x++) {
        for(int y = 0; y < 5; y++) { // 根据上一行的情况检查当前行是否需要变
            int up = (x - 1) * 5 + y;
            if(((1 << up) & s) == 0) { // 上一行该列是0 需要操作一次
                change(x, y, s);
                cnt++;
            }
            if(cnt > 6) return cnt;
        }
    }
    return s == target ? cnt : 7; // 最终还要检查是否所有灯都已经打开了
}

int solve1(int s) {
    int res = 7;
    for(int u = 0; u < 32; u++) { // 枚举第一行的初始操作
        int cnt = 0, ts = s;
        for(int i = 0; i < 5; i++) {
            if(u & (1 << i)) {
                change(0, i, ts);
                cnt++;
            }
        }
        res = min(res, solve2(ts, cnt));
    }
    return res > 6 ? -1 : res;
}

int main() {
    int n;
    cin >> n;
    for(int k = 1; k <= n; k++) {
        string line;
        int s = 0;
        for(int i = 0; i < 5; i++) {
            cin >> line;
            for(int j = 0; j < 5; j++) {
                if(line[j] == '1')
                    s |= 1 << (i * 5 + j);
            }
        }
        cout << solve1(s) << endl;
    }
}