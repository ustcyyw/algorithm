/**
 * @Time : 2023/2/23-5:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if(gcd(sx, sy) != gcd(tx, ty)) return false;
        return check(sx, sy, tx, ty);
    }

    bool check(int sx, int sy, int tx, int ty){
        if(sx > tx || sy > ty) return false;
        if(sx == tx && sy == ty) return true;
        if(tx == ty) return false;
        if(tx > ty) {
            int t = max((tx - sx) / ty, 1);
            return check(sx, sy, tx - ty * t, ty);
        } else {
            int t = max((ty - sy) / tx, 1);
            return check(sx, sy, tx, ty - tx * t);
        }
    }
};

int main(){
    Solution s;
    s.reachingPoints(1,8,4,15);
    cout << 0 << endl;
}