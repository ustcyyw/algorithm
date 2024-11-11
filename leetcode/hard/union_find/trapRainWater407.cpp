/**
 * @Time : 2022/8/30-12:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个 m x n 的矩阵，其中的值均为非负整数，代表二维高度图每个单元的高度，请计算图中形状最多能接多少体积的雨水。

 

示例 1:



输入: heightMap = [[1,4,3,1,3,2],[3,2,1,3,2,4],[2,3,3,2,3,1]]
输出: 4
解释: 下雨后，雨水将会被上图蓝色的方块中。总的接雨水量为1+2+1=4。
示例 2:



输入: heightMap = [[3,3,3,3,3],[3,2,2,2,3],[3,2,1,2,3],[3,2,2,2,3],[3,3,3,3,3]]
输出: 10
 

提示:

m == heightMap.length
n == heightMap[i].length
1 <= m, n <= 200
0 <= heightMap[i][j] <= 2 * 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/trapping-rain-water-ii
 */
class Solution {
    /**
     * 比较容易想到枚举水的高度
     * 如果在特定高度下，低于水高度的地方设为0，高于或等于水高度的地方设为1
     * 俯视着看，这是一个二维的01矩阵，这一高度能盛放水的地方（水面）就是0所在的地方
     * 并且要求这些0被1包围着，因为不被包围就说明那里有缺口了，水会流出去
     * 而1所在的地方，这里是柱体
     * 把上述的每一层符合条件的0的面积相加，就得到了答案
     * 但是时间过于复杂
     *
     * 模拟水的高度从0开始升高，就是从低到高枚举水的高度
     * 这个过程中，水淹没的地方（放置0的地方）是从原先有水的地方逐渐外扩
     * 而柱子所在的地方（放置1的地方）则从边缘向内收缩
     * 就像海平面上升淹没海岛一样。
     *
     * 如果以0的视角观察，发现是逐渐连成片，就像并查集连接不同的点一样
     * 我们需要知道哪些水域会从缺口流出，哪些水域还是"内陆湖" 用valid[i] = 1 表示 区域id=i的区域还是有效"内陆湖"
     * 随着水位上升，水域总面积增加（用sum表示）
     * 并且会有不断有"内陆湖"变成有缺口的失效水域，失效水域的总面积用fail来表示
     * 那么这高度还能蓄水的面就就是 sum - fail
     *
     * 其它解释见注释
     */
    const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
public:
    int n, m, fail = 0, range = 2e4 + 1;
    vector<int> id, size, valid;
    int trapRainWater(vector<vector<int>>& height) {
        n = height.size(), m = height[0].size();
        int t = m * n;
        id = vector(t, 0);
        for(int i = 0; i < t; i++)
            id[i] = i;
        size = vector(t, 1), valid = vector(t, 1);
        // 桶排序，以便从低到高枚举水面高度
        vector<vector<vector<int>>> map;
        map.assign(range, {});
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                map[height[i][j]].push_back({i, j});
        }
        int res = 0, sum = 0;
        for(int i = 0; i < range; i++){
            vector<vector<int>>& cur = map[i];
            sum += cur.size(); // 水域总面积增加cur.size()
            for(vector<int>& pos : cur){ // 每一个新加入的水域，都要查看上下左右，是否与其它水域连成片
                check_and_union(height, pos[0], pos[1]);
            }
            res += sum - fail; // 这高度还能蓄水的面就就是 sum - fail
        }
        return res;
    }

    void check_and_union(vector<vector<int>>& height, int x, int y){
        int k = get_key(x, y);
        // 如果新的水域是边界，就要去查看它是被别的水域标记为已失效，它可能已经被connect过，所以要用find找到它现在的id
        if(x == 0 || y == 0 || x == n - 1 || y == m - 1){
            int curId = find(k);
            if(valid[curId] == 1){ // 如果它还是有效的，意味着它现在所在的分量全都失效
                fail += size[curId]; // 所以这里是+= size[curId]，而不是简单的fail++
                valid[curId] = 0; // 计算过一次之后，设置这个水面分量为失效
            }
        }
        for(int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx > n - 1 || ny > m - 1) continue;
            if(height[nx][ny] > height[x][y]) continue; // 其相邻位置的柱子高度更高，根本不是水域，没有连接的道理
            int nk = get_key(nx, ny);
            connect(k, nk);
        }
    }

    void connect(int p, int q){
        p = find(p), q = find(q);
        if(p == q) return;
        if(valid[p] == 0 && valid[q] == 0) //两块区域都已经是失效的
            id[p] = q;
        else if(valid[p] == 0){ // q还没有失效，将q这个分量合并到p中，于是就失效了，那么失效的水域增加size[q]
            id[q] = p;
            fail += size[q];
        } else if(valid[q] == 0){ // p还没失效
            id[p] = q;
            fail += size[p];
        } else { // 都没失效，正常更新分量的大小即可
            id[p] = q;
            size[q] += size[p];
        }
    }

    int find(int p){
        if(id[p] == p) return p;
        id[p] = find(id[p]);
        return id[p];
    }
    // 坐标映射到线性编号
    int get_key(int x, int y){
        return x * m + y;
    }
};

int main(){
    Solution s;
//    vector<vector<int>> height = {{3,3,3,3,3},{3,2,2,2,3},{3,2,1,2,3},{3,2,2,2,3},{3,3,3,3,3}};
    vector<vector<int>> height = {{2,2,2},{2,1,2},{2,1,2}};
    s.trapRainWater(height);
    cout << 0 << endl;
}