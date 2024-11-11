/**
 * @Time : 2022/7/22-12:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个二维整数数组 tiles ，其中 tiles[i] = [li, ri] ，表示所有在 li <= j <= ri 之间的每个瓷砖位置 j 都被涂成了白色。

同时给你一个整数 carpetLen ，表示可以放在 任何位置 的一块毯子。

请你返回使用这块毯子，最多 可以盖住多少块瓷砖。

 

示例 1：



输入：tiles = [[1,5],[10,11],[12,18],[20,25],[30,32]], carpetLen = 10
输出：9
解释：将毯子从瓷砖 10 开始放置。
总共覆盖 9 块瓷砖，所以返回 9 。
注意可能有其他方案也可以覆盖 9 块瓷砖。
可以看出，瓷砖无法覆盖超过 9 块瓷砖。
示例 2：



输入：tiles = [[10,11],[1,1]], carpetLen = 2
输出：2
解释：将毯子从瓷砖 10 开始放置。
总共覆盖 2 块瓷砖，所以我们返回 2 。
 

提示：

1 <= tiles.length <= 5 * 104
tiles[i].length == 2
1 <= li <= ri <= 109
1 <= carpetLen <= 109
tiles 互相 不会重叠 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-white-tiles-covered-by-a-carpet
 */
class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end());
        int res = 0, n = tiles.size();
        vector<int> sum = vector(n + 1, 0);
        for(int i = 1; i <= n; i++){
            vector<int> tile = tiles[i - 1];
            sum[i] = sum[i - 1] + tile[1] - tile[0] + 1;
        }
        for(int i = 0, j = 0; i < n && j < n; i++){
            while (j < n && tiles[i][0] + carpetLen > tiles[j][1]) j++; // 关键是细心看坐标的关系
            if(j == n || tiles[i][0] + carpetLen < tiles[j][0])
                res = max(res, sum[j] - sum[i]);
            else
                res = max(res, sum[j] - sum[i] + tiles[i][0] + carpetLen - tiles[j][0]);
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<vector<int>> arr = {{1,5},{10,11},{12,17},{19,25},{30,32}};
    s.maximumWhiteTiles(arr, 10);
    cout << 0 << endl;
}