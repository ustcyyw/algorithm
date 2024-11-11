/**
 * @Time : 2024/4/14-3:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛128 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) {
        sort(points.begin(), points.end());
        int n = points.size(), res = 0;
        for(int i = 0, j = 0; i < n; i = j) {
            int lo = points[i][0];
            while(j < n && points[j][0] - lo <= w) j++;
            res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}