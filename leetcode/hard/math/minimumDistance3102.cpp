/**
 * @Time : 2024/4/1-10:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛391 t4
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int vals[N][4];
class Solution {
public:
    /*
     * 两个点的曼哈顿距离 dis(i, j)
     * 假设两个点p1 = (x1, y1), p2 = (x2, y2)
     * p1在p2的左下 dis = x2 - x1 + y2 - y1 = x2 + y2 - (x1 + y1)
     * p1在p2的左上 dis = x2 - x1 + y1 - y2 = x2 - y2 - (x1 - y1)
     * p1在p2的右下
     * p1在p2的右上
     * 分别记为v1,v2,v3,v4
     * dis(i, j) = max{v1(i,j), v2(i,j), v3(i,j), v4(i,j)}
     * 对于确定的两个点 曼哈顿距离只由一个表达式计算，但是其它3个表达式计算出的值都会更小
     * 所以都计算后取最大 就是正确答案
     * 比如 p1 = (1,3), p2 = (5,4), v1 = 5 + 4 - (1 + 3) = 5
     * 如果用v2计算则是 5 - 4 - (1 - 3) = 3 < v1
     *
     * 求任意两个点的曼哈顿距离最大值 也就是求 max{dis(i, j), for 任意(i, j)}
     * = max{max{v1(i,j), v2(i,j), v3(i,j), v4(i,j)}, for 任意(i, j)}
     * = max{max{v1(i, j)}, max{v2(i,j)}, max{v3(i,j)}, max{v4(i,j)}}
     */
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size(), res = INT_MAX;
        vector<multiset<int>> sets;
        sets.assign(4, {});
        for(int i = 0; i < n; i++) {
            int x = points[i][0], y = points[i][1];
            vals[i][0] = x + y, vals[i][1] = x - y, vals[i][2] = y - x, vals[i][3] = -x - y;
            for(int j = 0; j < 4; j++)
                sets[j].insert(vals[i][j]);
        }
        for(int i = 0; i < n; i++) {
            int temp = 0;
            for(int j = 0; j < 4; j++) {
                multiset<int>& set = sets[j];
                int v = vals[i][j];
                set.erase(set.find(v));
                temp = max(temp, *set.rbegin() - *set.begin());
                set.insert(v);
            }
            res = min(res, temp);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}