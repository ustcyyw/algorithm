/**
 * @Time : 2022/6/18-2:21 AM
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
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：10.9 MB, 在所有 C++ 提交中击败了80.99%的用户
     */
    double inf = 1000000000.0;
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        vector<double> point;
        // 初略检验
        int up1 = max(start1[1], end1[1]), up2 = max(start2[1], end2[1]);
        int down1 = min(start1[1], end1[1]), down2 = min(start2[1], end2[1]);
        if(up1 < down2 || up2 < down1) return point;
        int hi1 = max(start1[0], end1[0]), hi2 = max(start2[0], end2[0]);
        int lo1 = min(start1[0], end1[0]), lo2 = min(start2[0], end2[0]);
        if(hi1 < lo1 || hi2 < lo2) return point;

        double k1 = get_k(start1, end1), k2 = get_k(start2, end2);
        if(k1 == inf && k2 == inf){ // 两条直线的斜率不存在
            if(start1[0] != start2[0]) return point;
            double y = max(down1, down2);
            point.push_back(start1[0]), point.push_back(y);
        }
        else if(k1 == inf) one_inf(start2, point, k2, start1[0], down1, up1);
        else if(k2 == inf) one_inf(start1, point, k1, start2[0], down2, up2);
        else { // 两条直线都存在斜率的情况
            double d1 = get_d(start1, k1), d2 = get_d(start2, k2);
            if(k1 == k2){ // 斜率相同
                if(d1 == d2) { // 斜率相同 d相同
                    double x = max(lo1, lo2), y = k1 * x + d1;
                    point.push_back(x), point.push_back(y);
                }
            } else {
                double x = (d2 - d1) / (k1 - k2), y = x * k1 + d1;
                if(lo1 <= x && x <= hi1 && lo2 <= x && x <= hi2
                   && down1 <= y && y <= up1 && down2 <= y && y <= up2)
                    point.push_back(x), point.push_back(y);
            }
        }
        return point;
    }

    // start 斜率存在的那条直线上的一点，k 该直线的斜率。 x 交点的横坐标，也就是斜率不存在的那条线的横坐标
    void one_inf(vector<int>& start, vector<double>& point, double k, double x, int down, int up){
        double d = get_d(start, k), y = k * x + d;
        if(y > up || y < down) return;
        point.push_back(x), point.push_back(y);
    }

    double get_k(vector<int>& start, vector<int>& end){
        double dx = end[0] - start[0];
        if(dx == 0) return inf;
        return 1.0 * (end[1] - start[1]) / dx;
    }

    double get_d(vector<int>& point, double k){
        return point[1] - 1.0 * k * point[0];
    }
};

int main(){
    Solution s;
    vector<int> start1 = {1,1}, end1 = {-1,1}, start2 = {1,0}, end2 = {-3,2};
//    s.intersection(start1, end1, start2, end2);
    cout << s.intersection(start1, end1, start2, end2)[1] << endl;
}