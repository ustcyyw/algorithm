/**
 * @Time : 2022/8/10-12:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * Alice 和 Bob 是一场射箭比赛中的对手。比赛规则如下：

Alice 先射 numArrows 支箭，然后 Bob 也射 numArrows 支箭。
分数按下述规则计算：
箭靶有若干整数计分区域，范围从 0 到 11 （含 0 和 11）。
箭靶上每个区域都对应一个得分 k（范围是 0 到 11），Alice 和 Bob 分别在得分 k 区域射中 ak 和 bk 支箭。如果 ak >= bk ，那么 Alice 得 k 分。如果 ak < bk ，则 Bob 得 k 分
如果 ak == bk == 0 ，那么无人得到 k 分。
例如，Alice 和 Bob 都向计分为 11 的区域射 2 支箭，那么 Alice 得 11 分。如果 Alice 向计分为 11 的区域射 0 支箭，但 Bob 向同一个区域射 2 支箭，那么 Bob 得 11 分。

给你整数 numArrows 和一个长度为 12 的整数数组 aliceArrows ，该数组表示 Alice 射中 0 到 11 每个计分区域的箭数量。现在，Bob 想要尽可能 最大化 他所能获得的总分。

返回数组 bobArrows ，该数组表示 Bob 射中 0 到 11 每个 计分区域的箭数量。且 bobArrows 的总和应当等于 numArrows 。

如果存在多种方法都可以使 Bob 获得最大总分，返回其中 任意一种 即可。

 

示例 1：



输入：numArrows = 9, aliceArrows = [1,1,0,1,0,0,2,1,0,1,2,0]
输出：[0,0,0,0,1,1,0,0,1,2,3,1]
解释：上表显示了比赛得分情况。
Bob 获得总分 4 + 5 + 8 + 9 + 10 + 11 = 47 。
可以证明 Bob 无法获得比 47 更高的分数。
示例 2：



输入：numArrows = 3, aliceArrows = [0,0,1,0,0,0,0,0,0,0,0,2]
输出：[0,0,0,0,0,0,0,0,1,1,1,0]
解释：上表显示了比赛得分情况。
Bob 获得总分 8 + 9 + 10 = 27 。
可以证明 Bob 无法获得比 27 更高的分数。
 

提示：

1 <= numArrows <= 105
aliceArrows.length == bobArrows.length == 12
0 <= aliceArrows[i], bobArrows[i] <= numArrows
sum(aliceArrows[i]) == numArrows


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-points-in-an-archery-competition
 */
class Solution {
public:
    /**
     * 执行用时：52 ms, 在所有 C++ 提交中击败了77.06%的用户
     * 内存消耗：9.7 MB, 在所有 C++ 提交中击败了80.28%的用户
     *
     * 只有12个位置，用二进制来表示bob在某一环是否获胜
     * for(int s = start; s; s = (s - 1) & start) 枚举所有非空子集
     * 每一种集合表示的bob获胜状态，要统计得分且统计射箭数量 数量超过numArrows就非法
     */
    vector<int> maximumBobPoints(int numArrows, vector<int>& aliceArrows) {
        int start = (1 << 12) - 1, max_point = 0, state = 0;
        for(int s = start; s; s = (s - 1) & start){
            int point = 0, cost = 0;
            for(int i = 0, mask = 1; i < 12; i++){
                if((mask << i) & s) {
                    point += i;
                    cost += aliceArrows[i] + 1;
                }
            }
            if(cost <= numArrows && point > max_point)
                state = s;
        }
        vector<int> res = vector(12, 0);
        int sum = 0;
        for(int i = 0, mask = 1; i < 12; i++){
            if((mask << i) & state){
                res[i] = aliceArrows[i] + 1;
                sum += res[i];
            }
        }
        res[0] += numArrows - sum; // 补满箭的数量
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}