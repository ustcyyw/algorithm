/**
 * @Time : 2025/2/15-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF665A 1600 暴力枚举 模拟
 */

/*
 * 人x时刻出发 x + ta时刻到达
 * b出发的车时刻为y，到达时刻是 y + tb
 * 满足 出发时间早于 x + ta, 并且在人出发前还没到达的车
 * y < x + ta, y + tb > x
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, a, ta, b, tb;
string s;

int get_time(string str) {
    int h = (str[0] - '0') * 10 + str[1] - '0';
    int m = (str[3] - '0') * 10 + str[4] - '0';
    return h * 60 + m;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> a >> ta >> b >> tb >> s;
        int lo = get_time("05:00"),  hi = get_time("23:59");
        int x = get_time(s), ans = 0;
        for(int y = lo; y <= hi; y += b) {
            if(y < x + ta && y + tb > x)
                ans++;
        }
        cout << ans;
    }
};