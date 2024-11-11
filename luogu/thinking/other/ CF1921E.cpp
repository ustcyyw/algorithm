/**
 * @Time : 2024/11/8-5:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1921E 思维题
 */
 /*
  * 两个人的高度差 dh = x2 - x1
高度差为偶数 比如2、4。这种情况下a是不可能赢的 因为同一行的那一步 只可能是b走
所以a要想办法不输 在交汇的那一次操作中 列坐标差 >= 1
1. a和b列坐标差 <= 1 那a朝什么方向运动 b就跟着同步运动就行
    假设ya < yb，a应该尽可能往左走
2. a和b列坐标差 > 1 假设 ya < yb
    2.1 a向左下移动 b也应该向左上移动
    2.2 a向下移动 b也应该向左上移动 去尽量缩小列差
    2.3 a向右下移动 相当于在靠近b了 那b也向左上移动 更近
    对于2.2 2.3的情况 a相当于自杀 所以a只会走左下

以上2种情况 a和b都是向左走
于是要看在相遇前 总共可以向左移动多少步 每个人可以操作的次数是 dh / 2
a向左走的距离就是 left_a = min(ya - 1, dh / 2)
b向左走的距离就是 left_b = min(yb - 1, dh / 2)
b能追及a的距离总共是 t = left_b - left_a, 如果 t >= yb - ya 那么b能赢 否则平局
ya > yb的情况类似讨论

高度差是奇数 比如1、3。这种情况下b是不可能赢的
同理 只是a和b角色互换，并且a可以多走一步
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 4e2;
int T, n, h, w, xa, ya, xb, yb;

string solve() {
    // 向下走的a已经在向上走的b下面了 那他们没有任何机会互相吃 只能走到边界
    if(xa >= xb) return "Draw";
    int dh = xb - xa, dt = abs(ya - yb), da, db;
    if(dh % 2 == 0) {
        if(ya < yb) da = min(ya - 1, dh / 2), db = min(yb - 1, dh / 2);
        else da = min(w - ya, dh / 2), db = min(w - yb, dh / 2);
        return db - da >= dt ? "Bob" : "Draw";
    } else {
        if(yb < ya) da = min(ya - 1, dh / 2 + 1), db = min(yb - 1, dh / 2);
        else da = min(w - ya, dh / 2 + 1), db = min(w - yb, dh / 2);
        return da - db >= dt ? "Alice" : "Draw";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> h >> w >> xa >> ya >> xb >> yb;
        cout << solve() << "\n";
    }
};