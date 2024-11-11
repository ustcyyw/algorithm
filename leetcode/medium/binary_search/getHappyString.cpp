/**
 * @Time : 2022/7/23-12:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 一个 「开心字符串」定义为：

仅包含小写字母 ['a', 'b', 'c'].
对所有在 1 到 s.length - 1 之间的 i ，满足 s[i] != s[i + 1] （字符串的下标从 1 开始）。
比方说，字符串 "abc"，"ac"，"b" 和 "abcbabcbcb" 都是开心字符串，但是 "aa"，"baa" 和 "ababbc" 都不是开心字符串。

给你两个整数 n 和 k ，你需要将长度为 n 的所有开心字符串按字典序排序。

请你返回排序后的第 k 个开心字符串，如果长度为 n 的开心字符串少于 k 个，那么请你返回 空字符串 。

 

示例 1：

输入：n = 1, k = 3
输出："c"
解释：列表 ["a", "b", "c"] 包含了所有长度为 1 的开心字符串。按照字典序排序后第三个字符串为 "c" 。
示例 2：

输入：n = 1, k = 4
输出：""
解释：长度为 1 的开心字符串只有 3 个。
示例 3：

输入：n = 3, k = 9
输出："cab"
解释：长度为 3 的开心字符串总共有 12 个 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"] 。第 9 个字符串为 "cab"
示例 4：

输入：n = 2, k = 7
输出：""
示例 5：

输入：n = 10, k = 100
输出："abacbabacb"
 

提示：

1 <= n <= 10
1 <= k <= 100


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n
 */
class Solution {
public:
    /**
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：6.1 MB, 在所有 C++ 提交中击败了49.56%的用户
     * 找规律
     */
    const vector<vector<int>> chars = {{1,2},{0,2},{0,1}};
    const vector<int> limit = {0, 3, 6, 12, 24, 48, 96, 192, 384, 768, 1536};
    string getHappyString(int n, int k) {
        if(k > limit[n]) return "";
        string res;
        // order 用于处理第一个字母是a，b，c中的哪一个，以及序列落在的区间序号[0,1,2]，要特别处理k刚好能除尽区间长度的情况
        int interval = limit[n] / 3, order = k % interval == 0 ? k / interval - 1 : interval - 1;
        res.push_back((char)(order + 'a'));
        int l = interval * order + 1, r = interval * (order + 1);
        for(int i = 1; i < n; i++){
            int pre = res[i - 1] - 'a', mid = (l + r) >> 1;
            if(k <= mid) {
                res.push_back((char)(chars[pre][0] + 'a'));
                r = mid;
            } else {
                res.push_back((char)(chars[pre][1] + 'a'));
                l = mid + 1;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}