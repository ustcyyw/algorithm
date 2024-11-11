/**
 * @Time : 2024/2/28-4:23 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bl, vector<vector<int>>& tr) {
        long long n = bl.size(), res = 0;
        for(int i = 0; i < n; i++) {
            int x1 = bl[i][0], y1 = bl[i][1], x2 = tr[i][0], y2 = tr[i][1];
            for(int j = i + 1; j < n; j++) {
                res = max(res, cal(x1, y1, x2, y2, bl[j][0], bl[j][1], tr[j][0], tr[j][1]));
            }
        }
        return res;
    }

    long long cal(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
        if(x1 >= x4 || x2 <= x3 || y1 >= y4 || y2 <= y3) return 0; // 不相交判断
        if(x1 > x3) swap(x1, x3), swap(x2, x4); // 保证x1那个矩阵最靠左边
        if(y1 > y3) swap(y1, y3), swap(y2, y4); // y维度和x维度独立 也类似保证y1那个矩阵最靠下
        // x4 <= x2，x维度矩阵2被包含了 相交取决于x4 - x3， 否则是x2 - x3
        int t1 = x4 <= x2 ? x4 - x3 : x2 - x3;
        int t2 = y4 <= y2 ? y4 - y3 : y2 - y3;
        long long t = min(t1, t2);
        return t * t;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}