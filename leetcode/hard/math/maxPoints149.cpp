/**
 * @Time : 2023/3/23-7:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size(), res = 1;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++)
                res = max(res, count(points, i, j));
        }
        return res;
    }

    int count(vector<vector<int>>& points, int i, int j){
        int x1 = points[i][0], y1 = points[i][1], x2 = points[j][0], y2 = points[j][1];
        int res = 0;
        if(x1 == x2) {
            for(auto& point : points)
                if(point[0] == x1) res++;
            return res;
        }
        double k = (y2 - y1) * 1.0 / (x2 - x1), b = y1 - k * x1;
        for(auto& point : points){
            int x = point[0], y = point[1];
            if(abs(y - k * x - b) < 1e-6)
                res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{1,1},{1,4},{2,3},{3,2},{4,1},{5,3}};
    s.maxPoints(arr);
    cout << 0 << endl;
}