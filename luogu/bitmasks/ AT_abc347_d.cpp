/**
 * @Time : 2024/4/1-8:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * c中为0的地方 要么都是0 要么都是1。c中为1的地方 选其中一个放1
  * 枚举都放1的数量 检查是否可行
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, a, b, c, one, zero;

bool check(int cnt) {
    int ta = a - cnt; // a中单独放1的数量
    int tb = one - ta; // b中单独放1的数量
    if(ta < 0 || tb < 0 || tb + cnt != b) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b >> c;
    zero = 0, one = 0;
    for(int i = 0; i < 60; i++) {
        if((1ll << i) & c) one++;
        else zero++;
    }
    // 枚举在c中0数位的地方 a和b都放1的数量
    for(int cnt = 0; cnt <= min({zero, a, b}); cnt++) {
        if(!check(cnt)) continue;
        int ta = a - cnt, tb = one - ta;
        ll num1 = 0, num2 = 0;
        for(int i = 0; i < 60; i++) {
            ll t = 1ll << i;
            if(t & c) {
                if(ta) num1 |= t, ta--;
                else num2 |= t, tb--;
            } else { // c中该位为0 先将两个数该位都置为1 直到公共1数量满足
                if(cnt > 0) num1 |= t, num2 |= t, cnt--;
            }
        }
        cout << num1 << " " << num2;
        return 0;
    }
    cout << -1;
};