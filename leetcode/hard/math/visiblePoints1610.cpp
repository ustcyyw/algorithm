/**
 * @Time : 2022/12/29-8:30 PM
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
     * 向量a和b，取b = (1, 0)为计算方向的基准 |b| = 1
     * a = (x2 - x1, y2 - y1)
     * a点乘b = x2 - x1 = |a||b|cos<ang> = |a|cos<ang>
     * cos<ang> = x2 - x1 / |a|
     *
     * 人所在的点与要看的点的连线简称为线
     * 线与b = (1, 0)的夹角唯一确定，通过cos函数的反函数得出夹角度数
     * 注意反函数求出的值还要根据线的向量判断取正值还是负值
     *
     * 贪心的想，要让视角中的点尽可能的多，让视角的一个边界刚好落到其中一条线
     * 这样囊括的点最多
     * 枚举每一条线作为一个边界，根据度数确定有多少个点落在视野中
     * 假设作为起点的那条线角度为lo，那么另外一个边界就是hi = lo + angle
     * 随着lo增大，hi也单调增，于是想到了双指针，根据线的度数排序
     *
     * 注意：
     * 1.度数是360时，可以直接返回所有点都能看到
     * 2.有些点与人站的点重合，这些点在计算cos值的时候就出错了，因为单独处理，这些点是必定能看到的
     * 3.使用双指针找点时，double类型的比较，不能直接使用等号，要采用控制精度的办法，比如附加1e-5
     * 4.度数大的线，加上angle会超过360度，也就是转了一圈后又将度数低的线囊括进去了。
     *   要处理这种情况，只需要在计算度数的时候，每个度数再添加360后存放进去。
     *   （因为angle=360的情况直接特殊处理了，这样做不会使答案错误）
     */
    double pai = acos(-1);
    int visiblePoints(vector<vector<int>>& points, int angle, vector<int>& location) {
        if(angle == 360) return points.size();
        int x = location[0], y = location[1], cnt = 0;
        vector<double> angles;
        for(auto& point : points){
            int x1 = point[0], y1 = point[1];
            if(x == x1 && y == y1) {
                cnt++;
                continue;
            }
            int dx = x1 - x, dy = y1 - y;
            double cos_val = dx / sqrt(dx * dx + dy * dy);
            double ang = acos(cos_val) / pai * 180;
            if(dy < 0) ang *= -1; // 度数的处理 还要综合判断向量的方向（所在象限）
            angles.push_back(ang), angles.push_back(ang + 360);
        }
        int n = angles.size(), res = 0;
        sort(angles.begin(), angles.end());
        for(int i = 0, j = 0; i < n; i++){
            while (j < n && angles[j] - angles[i] <= angle + 1e-5) j++;
            res = max(res, j - i);
        }
        return res + cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}