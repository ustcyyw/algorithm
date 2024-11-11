/**
 * @Time : 2022/8/2-11:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个二维整数数组 circles ，其中 circles[i] = [xi, yi, ri] 表示网格上圆心为 (xi, yi) 且半径为 ri 的第 i 个圆，返回出现在 至少一个 圆内的 格点数目 。

注意：

格点 是指整数坐标对应的点。
圆周上的点 也被视为出现在圆内的点。
 

示例 1：



输入：circles = [[2,2,1]]
输出：5
解释：
给定的圆如上图所示。
出现在圆内的格点为 (1, 2)、(2, 1)、(2, 2)、(2, 3) 和 (3, 2)，在图中用绿色标识。
像 (1, 1) 和 (1, 3) 这样用红色标识的点，并未出现在圆内。
因此，出现在至少一个圆内的格点数目是 5 。
示例 2：



输入：circles = [[2,2,2],[3,4,1]]
输出：16
解释：
给定的圆如上图所示。
共有 16 个格点出现在至少一个圆内。
其中部分点的坐标是 (0, 2)、(2, 0)、(2, 4)、(3, 2) 和 (4, 4) 。
 

提示：

1 <= circles.length <= 200
circles[i].length == 3
1 <= xi, yi <= 100
1 <= ri <= min(xi, yi)

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-lattice-points-inside-a-circle
 */
class Solution {
public:
    int t = 1000;
    int countLatticePoints(vector<vector<int>>& circles) {
        unordered_set<int> set;
        for(vector<int>& c : circles){
            int x = c[0], y = c[1], r = c[2], rs = r * r;
            for(int i = r - y; i <= r + y; i++){
                for(int j = x ; ; j++){
                    int t1 = abs(i - y), t2 = abs(j - x);
                    if(rs < t1 * t1 + t2 * t2) break;
                    set.insert(i * t + j);
                }
            }
        }
        return set.size();
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}