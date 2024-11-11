/**
 * @Time : 2023/3/16-11:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        sort(points.begin(), points.end(), [](auto& a, auto& b) -> bool {return a[0] < b[0];});
        int n = points.size(), res = points[n - 1][0] - points[n - 2][0];
        for(int i = 0; i < n - 1; i++)
            res = max(res, points[i + 1][0] - points[i][0]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}