/**
 * @Time : 2022/8/25-8:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 游戏中存在两种角色：

好人：该角色只说真话。
坏人：该角色可能说真话，也可能说假话。
给你一个下标从 0 开始的二维整数数组 statements ，大小为 n x n ，表示 n 个玩家对彼此角色的陈述。具体来说，statements[i][j] 可以是下述值之一：

0 表示 i 的陈述认为 j 是 坏人 。
1 表示 i 的陈述认为 j 是 好人 。
2 表示 i 没有对 j 作出陈述。
另外，玩家不会对自己进行陈述。形式上，对所有 0 <= i < n ，都有 statements[i][i] = 2 。

根据这 n 个玩家的陈述，返回可以认为是 好人 的 最大 数目。

 

示例 1：


输入：statements = [[2,1,2],[1,2,2],[2,0,2]]
输出：2
解释：每个人都做一条陈述。
- 0 认为 1 是好人。
- 1 认为 0 是好人。
- 2 认为 1 是坏人。
以 2 为突破点。
- 假设 2 是一个好人：
    - 基于 2 的陈述，1 是坏人。
    - 那么可以确认 1 是坏人，2 是好人。
    - 基于 1 的陈述，由于 1 是坏人，那么他在陈述时可能：
        - 说真话。在这种情况下会出现矛盾，所以假设无效。
        - 说假话。在这种情况下，0 也是坏人并且在陈述时说假话。
    - 在认为 2 是好人的情况下，这组玩家中只有一个好人。
- 假设 2 是一个坏人：
    - 基于 2 的陈述，由于 2 是坏人，那么他在陈述时可能：
        - 说真话。在这种情况下，0 和 1 都是坏人。
            - 在认为 2 是坏人但说真话的情况下，这组玩家中没有一个好人。
        - 说假话。在这种情况下，1 是好人。
            - 由于 1 是好人，0 也是好人。
            - 在认为 2 是坏人且说假话的情况下，这组玩家中有两个好人。
在最佳情况下，至多有两个好人，所以返回 2 。
注意，能得到此结论的方法不止一种。
示例 2：


输入：statements = [[2,0],[0,2]]
输出：1
解释：每个人都做一条陈述。
- 0 认为 1 是坏人。
- 1 认为 0 是坏人。
以 0 为突破点。
- 假设 0 是一个好人：
    - 基于与 0 的陈述，1 是坏人并说假话。
    - 在认为 0 是好人的情况下，这组玩家中只有一个好人。
- 假设 0 是一个坏人：
    - 基于 0 的陈述，由于 0 是坏人，那么他在陈述时可能：
        - 说真话。在这种情况下，0 和 1 都是坏人。
            - 在认为 0 是坏人但说真话的情况下，这组玩家中没有一个好人。
        - 说假话。在这种情况下，1 是好人。
            - 在认为 0 是坏人且说假话的情况下，这组玩家中只有一个好人。
在最佳情况下，至多有一个好人，所以返回 1 。
注意，能得到此结论的方法不止一种。
 

提示：

n == statements.length == statements[i].length
2 <= n <= 15
statements[i][j] 的值为 0、1 或 2
statements[i][i] == 2

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-good-people-based-on-statements
 */
class Solution {
public:
    /**
     * 执行用时：76 ms, 在所有 C++ 提交中击败了86.14%的用户
     * 内存消耗：8.1 MB, 在所有 C++ 提交中击败了61.39%的用户
     *
     * 由于只有15个人，每个人只有好人 坏人2个状态，想到状态压缩
     * 用一个二进制数表示每个人的好人坏人情况，某一位为1表示那个人是好人
     *
     * 一个坏人说的话，直接无视就行
     * 好人说的话必须挨个检查，如果都符合好人们说的话，说明这种情况是成立的，就是一个备选答案
     * 一个好人如果对对方没有判断，也就是statements[i][j] == 2，就也直接无视
     * 另外两种情况就根据对应位置的二进制位上的情况来判断是否出现矛盾
     */
    int n;
    int maximumGood(vector<vector<int>>& statements) {
        n = statements.size();
        int u = (1 << n) - 1, res = 0;
        for(int s = u; s; s = (s - 1) & u){
            res = max(res, check(statements, s));
        }
        return res;
    }
    // state中的1表示这是个好人
    int check(vector<vector<int>>& statements, int state){
        for(int i = 0; i < n; i++){
            if(((1 << i) & state) == 0) continue; // 坏人的话没必要听
            auto& info = statements[i];
            for(int j = 0; j < n; j++){
                if(info[j] == 2) continue; // 没有判断则无效检查
                int t = 1 << j;
                if(info[j] == 1 && !(t & state)) return 0;
                if(info[j] == 0 && (t & state)) return 0;
            }
        }
        return bit_count(state);
    }

    int bit_count(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        i = (i + (i >> 4)) & 0x0f0f0f0f;
        i = i + (i >> 8);
        i = i + (i >> 16);
        return i & 0x3f;
    }
};

int main(){
    Solution s;
    vector<vector<int>> statements = {{2,1,2},{1,2,2},{2,0,2}};
    s.check(statements, 6);
    cout << s.bit_count(5) << endl;
}