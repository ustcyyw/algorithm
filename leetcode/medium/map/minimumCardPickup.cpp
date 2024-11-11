/**
 * @Time : 2022/7/30-2:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 cards ，其中 cards[i] 表示第 i 张卡牌的 值 。如果两张卡牌的值相同，则认为这一对卡牌 匹配 。

返回你必须拿起的最小连续卡牌数，以使在拿起的卡牌中有一对匹配的卡牌。如果无法得到一对匹配的卡牌，返回 -1 。

 

示例 1：

输入：cards = [3,4,2,3,4,7]
输出：4
解释：拿起卡牌 [3,4,2,3] 将会包含一对值为 3 的匹配卡牌。注意，拿起 [4,2,3,4] 也是最优方案。
示例 2：

输入：cards = [1,0,5,3]
输出：-1
解释：无法找出含一对匹配卡牌的一组连续卡牌。
 

提示：

1 <= cards.length <= 105
0 <= cards[i] <= 106

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-consecutive-cards-to-pick-up
 */
class Solution {
public:
    /**
     * 执行用时：248 ms, 在所有 C++ 提交中击败了77.46%的用户
     * 内存消耗：112.3 MB, 在所有 C++ 提交中击败了79.92%的用户
     */
    int minimumCardPickup(vector<int>& cards) {
        unordered_map<int, int> map;
        int max_val = 1000000, res = max_val;
        for(int i = 0; i < cards.size(); i++){
            int card = cards[i];
            if(map.count(card)) res = min(i - map[card] + 1, res);
            map[card] = i;
        }
        return res == max_val ? -1 : res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}