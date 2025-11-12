/**
 * @Time : 2024/5/10-9:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1154C 模拟
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, b, a, c, sa, sb, sc, type[7] = {1, 2, 3, 1, 3, 2, 1};

bool move(int& day, int start) {
    for(int i = start; i < 7; i++, day++) {
        int t = type[i];
        if(t == 1) {
            if(a > 0) a--;
            else return false;
        } else if(t == 2) {
            if(b > 0) b--;
            else return false;
        } else {
            if(c > 0) c--;
            else return false;
        }
    }
    return true;
}

int cal(int start) {
    int day = 0;
    a = sa, b = sb, c = sc;
    if(!move(day, start)) return day;
    int t = min({a / 3, b / 2, c / 2});
    day += 7 * t;
    a -= t * 3, b -= t * 2, c -= t * 2;
    move(day, 0);
    return day;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> sa >> sb >> sc;
    int ans = 0;
    for(int i = 0; i < 7; i++) {
        ans = max(ans, cal(i));
    }
    cout << ans;
};