/**
 * @Time : 2022/7/23-10:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个长度为 n 的整数数组 rolls 和一个整数 k 。你扔一个 k 面的骰子 n 次，骰子的每个面分别是 1 到 k ，其中第 i 次扔得到的数字是 rolls[i] 。
 *
 * 请你返回 无法 从 rolls 中得到的 最短 骰子子序列的长度。
 *
 * 扔一个 k 面的骰子 len 次得到的是一个长度为 len 的 骰子子序列 。
 *
 * 注意 ，子序列只需要保持在原数组中的顺序，不需要连续。
 *
 *  
 *
 * 示例 1：
 *
 * 输入：rolls = [4,2,1,2,3,3,2,4,1], k = 4
 * 输出：3
 * 解释：所有长度为 1 的骰子子序列 [1] ，[2] ，[3] ，[4] 都可以从原数组中得到。
 * 所有长度为 2 的骰子子序列 [1, 1] ，[1, 2] ，... ，[4, 4] 都可以从原数组中得到。
 * 子序列 [1, 4, 2] 无法从原数组中得到，所以我们返回 3 。
 * 还有别的子序列也无法从原数组中得到。
 * 示例 2：
 *
 * 输入：rolls = [1,1,2,2], k = 2
 * 输出：2
 * 解释：所有长度为 1 的子序列 [1] ，[2] 都可以从原数组中得到。
 * 子序列 [2, 1] 无法从原数组中得到，所以我们返回 2 。
 * 还有别的子序列也无法从原数组中得到，但 [2, 1] 是最短的子序列。
 * 示例 3：
 *
 * 输入：rolls = [1,1,3,2,2,2,3,3], k = 4
 * 输出：1
 * 解释：子序列 [4] 无法从原数组中得到，所以我们返回 1 。
 * 还有别的子序列也无法从原数组中得到，但 [4] 是最短的子序列。
 *  
 *
 * 提示：
 *
 * n == rolls.length
 * 1 <= n <= 105
 * 1 <= rolls[i] <= k <= 105
 *
 * 来源：力扣（LeetCode）
 * 链接：https://algorithm.cn/problems/shortest-impossible-sequence-of-rolls
 */
class Solution {
public:
    /**
     * 任何数字都可以出现在第一位，第二位...
     * 首先考虑第一位出现的数字：显然rolls中得出现所有的数字，否则无法得到的序列最短长度就是1
     * 如果所有数字都出现在rolls中，那么他们后继的第二个数字，也是任何数字
     * 要在数组的右边位置去找后继数字，如果有某一个数字找不到了，无法得到的最短序列长度就是2
     * 以此类推
     * 于是关注同一个数字出现的位置，以及他们之间的相对位置很重要
     *
     * 首先：
     * 同一个数字的不同位置的考虑。例如序列 4 x x x 4 x x
     * 在讨论以4开头的序列时，显然选第一个4更可能得到所有的可能序列（第2个4后面可选的数字，第一个4都能选到）
     * 因此对于同一个数字，我们要优先找最靠前
     *
     * 对于不同数字的位置考虑
     * 以序列 4 3 2 1 x x x
     * 长度为1的序列已经齐全，找长度2的序列
     * 显然以4为开头的序列，第二个数字更容易找全，3次之，1最难
     * 但由于我们要找的是最短的不可能出现的数字，因此应该优先考虑1是不是能凑全所有第二个数字
     * 如果1可以，则4 3 2一定可以。
     *
     * 综上，贪心的做法就是在每一轮找全数字时，关注同一个数字的最左位置
     * 下一轮找数字时，则从这一轮的数字中最靠右的开始考虑，这样能最早发现不能凑齐的序列
     *
     * 要关注同一个数字的最左位置，我们就使用map嵌套队列
     * 关注每一轮数字中最靠右的，就使用临时变量temp_last来更新，然后下一轮从这个位置的右边去找下一位数字
     * 于是每一轮中都要去掉已经在last左边的数。
     * 如果发现某个队列中已经没有元素来，就说明无法找到对应的数字，得到答案。
     * 轮次数就是序列的长度。
     */
    int shortestSequence(vector<int>& rolls, int k) {
        vector<queue<int>> indexs;
        indexs.assign(k + 1, {});
        for(int i = 0; i < rolls.size(); i++)
            indexs[rolls[i]].push(i);
        int res = 1, last = -1, flag = 0;
        while (true){
            int temp_last = 0;
            for(int i = 1; i <= k; i++){
                auto& cur = indexs[i]; // 一定要使用引用
                while (!cur.empty() && cur.front() <= last)
                    cur.pop();
                if(cur.empty())
                    flag = 1;
                temp_last = max(temp_last, cur.front());
            }
            if(flag) break;
            last = temp_last;
            res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}