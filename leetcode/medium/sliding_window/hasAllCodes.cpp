/**
 * @Time : 2022/8/19-9:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 *给你一个二进制字符串 s 和一个整数 k 。如果所有长度为 k 的二进制字符串都是 s 的子串，请返回 true ，否则请返回 false 。

 

示例 1：

输入：s = "00110110", k = 2
输出：true
解释：长度为 2 的二进制串包括 "00"，"01"，"10" 和 "11"。它们分别是 s 中下标为 0，1，3，2 开始的长度为 2 的子串。
示例 2：

输入：s = "0110", k = 1
输出：true
解释：长度为 1 的二进制串包括 "0" 和 "1"，显然它们都是 s 的子串。
示例 3：

输入：s = "0110", k = 2
输出：false
解释：长度为 2 的二进制串 "00" 没有出现在 s 中。
 

提示：

1 <= s.length <= 5 * 105
s[i] 不是'0' 就是 '1'
1 <= k <= 20

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/check-if-a-string-contains-all-binary-codes-of-size-k
 */
class Solution {
public:
    /**
     * 执行用时：48 ms, 在所有 C++ 提交中击败了92.81%的用户
     * 内存消耗：19.6 MB, 在所有 C++ 提交中击败了88.89%的用户
     */
    bool hasAllCodes(string s, int k) {
        vector<bool> marked = vector(1 << k, false);
        int cur = 0, remove = 1 << k, left = 0, right = 0, count = 0, n = s.size();
        while (right < n){
            cur <<= 1;
            cur += s[right] - '0';
            if(right - left + 1 > k)
                cur -= (s[left++] - '0') * remove;
            if(right - left + 1 == k && !marked[cur]){
                marked[cur] = true;
                count++;
                if(count == (1 << k)) return true;
            }
            right++;
        }
        return false;
    }
};

int main(){
    Solution s;
    s.hasAllCodes("00110110",2);
    cout << 0 << endl;
}