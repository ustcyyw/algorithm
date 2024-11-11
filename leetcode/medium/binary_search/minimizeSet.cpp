/**
 * @Time : 2022/12/26-3:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeSet(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
        long lc = lcm((long)divisor1, (long)divisor2);
        int lo = 2, hi = INT_MAX, total = uniqueCnt1 + uniqueCnt2;
        while (lo < hi){
            int mid = (hi - lo) / 2 + lo;
            if(mid - mid / lc >= total && mid - mid / divisor1 >= uniqueCnt1
               && mid - mid / divisor2 >= uniqueCnt2) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

    /**
     * 只能放在第一组的:会被d2除尽的部分 - 这部分中还能被d1除尽的
     * cnt1 = mid / d2 - mid / lcm
     * 同理 cnt2 = mid / d1 - mid / lcm
     * 两边都可以放置的: 总的 - 会被d2除尽的 - 会被d1除尽的 + 会被d1和d2同时除尽的（因为重复减掉了这部分）
     * common = mid - mid / d1 - mid / d1 + mid / lcm
     *
     * uniqueCnt1 - cnt1：就是将只能放在第1组的先放进去，还缺多少个数，却的就需要从两边都可以放置的那部分中取
     * uniqueCnt2 - cnt2：就是将只能放在第2组的先放进去，还缺多少个数
     */
    int minimizeSet2(int divisor1, int divisor2, int uniqueCnt1, int uniqueCnt2) {
        long lc = lcm((long)divisor1, (long)divisor2);
        int lo = 2, hi = 2e9 + 1;
        while (lo < hi){
            int mid = (hi - lo) / 2 + lo, t = mid / lc;
            int cnt1 = mid / divisor2 - t, cnt2 = mid / divisor1 - t;
            long common = mid - mid / divisor2 - mid / divisor1 + t;
            if(common >= (max(uniqueCnt1 - cnt1, 0) + max(uniqueCnt2 - cnt2, 0))) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}