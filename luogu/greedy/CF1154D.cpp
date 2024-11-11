/**
 * @Time : 2024/5/10-8:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1154D 贪心
 */
 /*
  * 1. 无阳光的情况下
        1.1 还有蓄电池 肯定用蓄电池 普通电池留着有太阳的时候用 给充电电池充电
        2.1 无蓄电池了 那只能用普通电池了
    2. 有太阳的情况下
        2.1 普通电池没有了或者蓄电池是满电 使用蓄电池
        2.2 否则 使用普通电池 让蓄电池充电
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, b, a;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> b >> a;
    int cb = b, ca = a;
    for(int i = 0, num; i <= n; i++) {
        if((ca == 0 && cb == 0) || i == n) {
            cout << i;
            break;
        }
        cin >> num;
        if(num == 0) {
            if(ca > 0) ca--;
            else cb--;
        } else {
            if(ca == a || cb == 0) ca--;
            else cb--, ca++;
        }
    }
};