/**
 * @Time : 2024/9/5-3:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1216C 数学 计算几何
 */
 /*
  * 画图 分情况讨论
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, a1, b1, a2, b2, a3, b3, a4, b4, a5, b5, a6, b6;

// 矩形(x1,y1,x2,y2) 是否在 矩形(x3,y3,x4,y4)内部
bool in(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
    return x1 >= x3 && y1 >= y3 && x2 <= x4 && y2 <= y4;
}

bool cover1() {
    if(a4 <= a1 || a3 >= a2 || (a3 > a1 && a4 < a2)) return false;
    if(b4 < b2 || b3 > b1) return false;
    if(a4 < a2) return in(a4, b1, a2, b2, a5, b5, a6, b6);
    if(a3 > a1) return in(a1, b1, a3, b2, a5, b5, a6, b6);
    return false;
}

bool cover2() {
    if(b4 <= b1 || b3 >= b2 || (b3 > b1 && b4 < b2)) return false;
    if(a4 < a2 || a3 > a1) return false;
    if(b4 < b2) return in(a1, b4, a2, b2, a5, b5, a6, b6);
    if(b3 > b1) return in(a1, b1, a2, b3, a5, b5, a6, b6);
    return false;
}

bool check() {
    if(in(a1, b1, a2, b2, a3, b3, a4, b4) || in(a1, b1, a2, b2, a5, b5, a6, b6))
        return true;
    return cover1() || cover2();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T-- > 0) {
        cin >> a1 >> b1 >> a2 >> b2;
        cin >> a3 >> b3 >> a4 >> b4;
        cin >> a5 >> b5 >> a6 >> b6;
        cout << (!check() ? "YES" : "NO") << endl;
    }
};