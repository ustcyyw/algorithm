/**
 * @Time : 2025/11/3-21:08
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3733 1990 二分答案 数学 数论
 */
 /*
  * c1: 机器1充电的次数
c2: 机器2充电的次数
c12: 两个机器都在充电的次数

c1 - c12: 机器1充电 但是2不需要充电 安排2去
c2 - c12: 机器2充电 但是1不需要充电 安排1去

c1 + c2 - c12: 有机器在充电的
c - (c1 + c2 - c12): 没有机器充电
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    ll d1, d2, r1, r2;
    long long minimumTime(vector<int>& d, vector<int>& r) {
        ll lo = 1, hi = 1e15;
        d1 = d[0], d2 = d[1], r1 = r[0], r2 = r[1];
        while(lo < hi) {
            ll mid = (lo + hi) >> 1;
            if(check(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    bool check(ll c) {
        ll c1 = c / r1, c2 = c / r2, c12 = c / lcm(r1, r2);
        ll need1 = max(0ll, d1 - (c2 - c12)), need2 = max(0ll, d2 - (c1 - c12));
        return need1 + need2 <= c - (c1 + c2 - c12);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}