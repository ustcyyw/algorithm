/**
 * @Time : 2022/8/14-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你下标从 0 开始、长度为 n 的字符串 pattern ，它包含两种字符，'I' 表示 上升 ，'D' 表示 下降 。

你需要构造一个下标从 0 开始长度为 n + 1 的字符串，且它要满足以下条件：

num 包含数字 '1' 到 '9' ，其中每个数字 至多 使用一次。
如果 pattern[i] == 'I' ，那么 num[i] < num[i + 1] 。
如果 pattern[i] == 'D' ，那么 num[i] > num[i + 1] 。
请你返回满足上述条件字典序 最小 的字符串 num。

 

示例 1：

输入：pattern = "IIIDIDDD"
输出："123549876"
解释：
下标 0 ，1 ，2 和 4 处，我们需要使 num[i] < num[i+1] 。
下标 3 ，5 ，6 和 7 处，我们需要使 num[i] > num[i+1] 。
一些可能的 num 的值为 "245639871" ，"135749862" 和 "123849765" 。
"123549876" 是满足条件最小的数字。
注意，"123414321" 不是可行解因为数字 '1' 使用次数超过 1 次。
示例 2：

输入：pattern = "DDD"
输出："4321"
解释：
一些可能的 num 的值为 "9876" ，"7321" 和 "8742" 。
"4321" 是满足条件最小的数字。
 

提示：

1 <= pattern.length <= 8
pattern 只包含字符 'I' 和 'D' 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/construct-smallest-number-from-di-string
 */
class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：5.9 MB, 在所有 C++ 提交中击败了33.33%的用户
     */
    string smallestNumber(string pattern) {
        int min_num = 1, n = pattern.size(); // min_val 表示可用的最小数字
        vector<bool> used = vector(10, false);
        vector<int> counts = vector(n, 0);
        for(int i = n - 1, count = 1; i >= 0; i--){
            if(pattern[i] == 'D') counts[i] = count++;
            else count = 1;
        }
        string res;
        for(int i = 0; i < n; i++){
            if(pattern[i] == 'I') {
                res.push_back(char(min_num + '0'));
                used[min_num] = true;
            } else {
                res.push_back(char(min_num + counts[i] + '0'));
                used[min_num + counts[i]] = true;
            }
            while (min_num <= 9 && used[min_num]) min_num++;
        }
        res.push_back(char(min_num + '0'));
        return res;
    }
};

int main(){
    Solution s;
    s.smallestNumber("IIIDIDDD");
    cout << s.smallestNumber("IIIDIDDD") << endl;
}