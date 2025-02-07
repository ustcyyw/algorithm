/**
 * @Time : 2022/8/2-10:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个二维整数数组 rectangles ，其中 rectangles[i] = [li, hi] 表示第 i 个矩形长为 li 高为 hi 。给你一个二维整数数组 points ，其中 points[j] = [xj, yj] 是坐标为 (xj, yj) 的一个点。

第 i 个矩形的 左下角 在 (0, 0) 处，右上角 在 (li, hi) 。

请你返回一个整数数组 count ，长度为 points.length，其中 count[j]是 包含 第 j 个点的矩形数目。

如果 0 <= xj <= li 且 0 <= yj <= hi ，那么我们说第 i 个矩形包含第 j 个点。如果一个点刚好在矩形的 边上 ，这个点也被视为被矩形包含。

 

示例 1：



输入：rectangles = [[1,2],[2,3],[2,5]], points = [[2,1],[1,4]]
输出：[2,1]
解释：
第一个矩形不包含任何点。
第二个矩形只包含一个点 (2, 1) 。
第三个矩形包含点 (2, 1) 和 (1, 4) 。
包含点 (2, 1) 的矩形数目为 2 。
包含点 (1, 4) 的矩形数目为 1 。
所以，我们返回 [2, 1] 。
示例 2：



输入：rectangles = [[1,1],[2,2],[3,3]], points = [[1,3],[1,1]]
输出：[1,3]
解释：
第一个矩形只包含点 (1, 1) 。
第二个矩形只包含点 (1, 1) 。
第三个矩形包含点 (1, 3) 和 (1, 1) 。
包含点 (1, 3) 的矩形数目为 1 。
包含点 (1, 1) 的矩形数目为 3 。
所以，我们返回 [1, 3] 。
 

提示：

1 <= rectangles.length, points.length <= 5 * 104
rectangles[i].length == points[j].length == 2
1 <= li, xj <= 109
1 <= hi, yj <= 100
所有 rectangles 互不相同 。
所有 points 互不相同 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/count-number-of-rectangles-containing-each-point
*/
class Solution {
public:
    vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
        unordered_set<int> x_set, y_set;
        for(vector<int>& r : rectangles)
            x_set.insert(r[0]), y_set.insert(r[1]);
        for(vector<int>& p : points)
            x_set.insert(p[0]), y_set.insert(p[0]);
        unordered_map<int, int> x_map = scatter(x_set), y_map = scatter(y_set);
        int m = x_map.size(), n = y_map.size();
        vector<vector<int>> grid = vector(m, vector(n, 0)), sum = vector(m, vector(n, 0));
        for(vector<int>& r : rectangles)
            grid[x_map[r[0]]][y_map[r[1]]]++;
        // 计算后缀和
        sum[m - 1][n - 1] = grid[m - 1][n - 1];
        for(int i = n - 2; i >= 0; i--)
            sum[m - 1][i] = sum[m - 1][i + 1] + grid[m - 1][i];
        for(int i = m - 2; i >= 0; i--){
            for(int j = n - 1, temp = 0; j >= 0; j--){
                temp += grid[i][j];
                sum[i][j] = temp + sum[i + 1][j];
            }
        }
        vector<int> res;
        for(vector<int>& p : points)
            res.push_back(sum[x_map[p[0]]][x_map[p[1]]]);
        return res;
    }

    unordered_map<int, int> scatter(unordered_set<int>& set){
        vector<int> nums;
        for(int num : set) nums.push_back(num);
        sort(nums.begin(), nums.end());
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++)
            map[nums[i]] = i;
        return map;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}