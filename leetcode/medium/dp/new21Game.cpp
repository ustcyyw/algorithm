/**
 * @Time : 2022/8/12-11:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 爱丽丝参与一个大致基于纸牌游戏 “21点” 规则的游戏，描述如下：

爱丽丝以 0 分开始，并在她的得分少于 k 分时抽取数字。 抽取时，她从 [1, maxPts] 的范围中随机获得一个整数作为分数进行累计，其中 maxPts 是一个整数。 每次抽取都是独立的，其结果具有相同的概率。

当爱丽丝获得 k 分 或更多分 时，她就停止抽取数字。

爱丽丝的分数不超过 n 的概率是多少？

与实际答案误差不超过 10-5 的答案将被视为正确答案。

 
示例 1：

输入：n = 10, k = 1, maxPts = 10
输出：1.00000
解释：爱丽丝得到一张牌，然后停止。
示例 2：

输入：n = 6, k = 1, maxPts = 10
输出：0.60000
解释：爱丽丝得到一张牌，然后停止。 在 10 种可能性中的 6 种情况下，她的得分不超过 6 分。
示例 3：

输入：n = 21, k = 17, maxPts = 10
输出：0.73278
 

提示：

0 <= k <= n <= 104
1 <= maxPts <= 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/new-21-game
 */
class Solution {
public:
    /**
     * 执行用时：8 ms, 在所有 C++ 提交中击败了21.92%的用户
     * 内存消耗：10.4 MB, 在所有 C++ 提交中击败了36.30%的用户
     *
     * 动态规划，但是转移方程需要连续加上一个区间上的和，所以要用一个变量来累加
     * 但是要注意 如果分数大于k，是不可以从大于等于k的数上面转移过去的，因为游戏已经停止了
     */
    double new21Game(int n, int k, int maxPts) {
        if(k == 0) return 1;
        vector<double> p = vector(k + maxPts, 0.0);
        p[0] = 1;
        double sum = 1, res = 0;
        for(int i = 1; i < p.size(); i++){
            if(i - maxPts - 1 >= 0) sum -= p[i - maxPts - 1];
            p[i] = sum / maxPts;
            if(i < k) sum += p[i];
        }
        for(int i = k; i < min(n + 1, (int)p.size()); i++)
            res += p[i];
        return res;
    }
};

int main(){
    Solution s;
    s.new21Game(1,0,2);
    cout << s.new21Game(21,17,10) << endl;
}