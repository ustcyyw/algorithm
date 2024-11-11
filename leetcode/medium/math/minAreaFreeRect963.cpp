/**
 * @Time : 2022/11/7-1:02 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        double res = (double)LONG_MAX;
        int n = points.size(), t = 400001;
        unordered_set<int> set;
        for(auto& point : points)
            set.insert(t * point[0] + point[1]);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j == i) continue;
                vector<int> edge1 = {points[j][0] - points[i][0], points[j][1] - points[i][1]};
                double len1 = length(edge1);
                for(int k = 0; k < n; k++){
                    if(k == i || k == j) continue;
                    vector<int> edge2 = {points[k][0] - points[j][0], points[k][1] - points[j][1]};
                    if(!is_vertical(edge1, edge2)) continue;
                    double len2 = length(edge2);
                    vector<int> p4 = {points[k][0] - edge1[0], points[k][1] - edge1[1]};
                    if(set.count(p4[0] * t + p4[1]))
                        res = min(res, len1 * len2);
                }
            }
        }
        return res == (double)LONG_MAX ? 0 : res;
    }

    // 垂直就是点乘为0
    bool is_vertical(vector<int>& p1, vector<int>& p2){
        return p1[0] * p2[0] +  p1[1] * p2[1] == 0;
    }

    double length(vector<int>& p){
        return sqrt(p[0] * p[0] + p[1] * p[1]);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}