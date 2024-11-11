/**
 * @Time : 2022/12/6-11:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 容斥原理
     * |A并B并C| = |A| + |B| + |C| - |A交B| - |A交C| - |B交C| + |A交B交C|
     *
     * 本题中要求的是a b c三个数倍数集合的并集
     */
    int nthUglyNumber(int n, int a, int b, int c) {
        long long lcm_ab = lcm(a, b), lcm_ac = lcm(a, c), lcm_bc = lcm((long long)b, c);
        long long lcm_abc = lcm(lcm_ab, c);
        long lo = 1, hi = 2e9;
        while (lo < hi){
            long mid = lo + (hi - lo) / 2;
            long cnt = (long)mid / a + mid / b + mid / c - mid / lcm_ab - mid / lcm_ac - mid / lcm_bc + mid / lcm_abc;
            if(cnt >= n) hi = mid;
            else lo = mid + 1;
        }
        return (int)lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}