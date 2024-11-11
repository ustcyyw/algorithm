/**
 * @Time : 2022/8/11-8:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个只包含小写英文字母的字符串 s 。

每一次 操作 ，你可以选择 s 中两个 相邻 的字符，并将它们交换。

请你返回将 s 变成回文串的 最少操作次数 。

注意 ，输入数据会确保 s 一定能变成一个回文串。

 

示例 1：

输入：s = "aabb"
输出：2
解释：
我们可以将 s 变成 2 个回文串，"abba" 和 "baab" 。
- 我们可以通过 2 次操作得到 "abba" ："aabb" -> "abab" -> "abba" 。
- 我们可以通过 2 次操作得到 "baab" ："aabb" -> "abab" -> "baab" 。
因此，得到回文串的最少总操作次数为 2 。
示例 2：

输入：s = "letelt"
输出：2
解释：
通过 2 次操作从 s 能得到回文串 "lettel" 。
其中一种方法是："letelt" -> "letetl" -> "lettel" 。
其他回文串比方说 "tleelt" 也可以通过 2 次操作得到。
可以证明少于 2 次操作，无法得到回文串。
 

提示：

1 <= s.length <= 2000
s 只包含小写英文字母。
s 可以通过有限次操作得到一个回文串。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-number-of-moves-to-make-palindrome
 */
class Solution {
public:
    /**
     * 看test case2 像贪心
     * 固定左端点的字母，在后续的位置找到与之相等的字母，然后交换到成对的位置
     * 如x....x...交换之后变为x.......x，于是只需要关注剩下的子区间
     *
     * 这样的匹配方式为何正确?
     * 如果当前有两个可选的字符对，x和y，x中的一个在最左边
     * x......x...
     * y可能的位置情况有三种
     * 1. x..y..y..x.. 显然要把y放到最外面进行匹配，交换次数更高
     * 2. x.(a)..y.(b)..x.(c)..y.(d).. 中间括号中的字母表示x和y之间有多少个字母
     * 移动为xy....yx的交换次数
     * a：第一个y移动到左边；
     * c + 1 + d：第二个x移动到最右边
     * d：第二个y移动到最右边
     * 总的为 a + c + 2d + 1
     * 移动为yx....xy的交换次数
     * a + 1：第一个y移动到左边，此时第一个x在次左边
     * d：第二个y移动到最右边
     * c + d：第二个x移动到次右边
     * 总的为 a + c + 2d + 1
     * 是等价的
     * 3. x.(a)..y.(b)..y.(c)..x.(d)..
     * 同2的分析发现两种移动方式，需要的交换次数一致
     *
     * 因此固定未匹配区间的最左边元素，一定是最优的（至少是等价）
     *
     * 但是可能会存在字符串总长度为奇数的情况，也就是有一个字母最后会落单
     * 总会在某一个未匹配区间的第一个字母，遇到落单的情况，如
     * cabab 遇到了落单的c，先完成后续abab的回文匹配得到cabba，再将c移动到后续匹配完成的字符串的中间,得到abcba
     */
    int minMovesToMakePalindrome(string s) {
        int res = 0;
        for(int i = 0, j = s.size() - 1; i < j; i++){
            int k = j;
            while (s[i] != s[k]) k--;
            if(k == i) { // 说明遇到了单个的字符，它应该最终放在字符串的中间，剩余未配对的字符串长度是 j - i + 1
                res += (j - i) / 2; // 除去这个落单的，还有j-i个字符，最终要交换至中间需要(j - i) / 2次交换
                continue; // 这种情况，只应该左指针移动，未匹配的区间变成[i+1,j]
            }
            res += j - k;
            while (k < j) { // 交换之后，未匹配区间的字符串需要更新
                s[k] = s[k + 1];
                k++;
            }
            j--; // 这种情况为匹配的区间变为[i+1,j-1]，所有这里要j--
        }
        return res;
    }
};

int main(){
    Solution s;
    s.minMovesToMakePalindrome("aabb");
    cout << 0 << endl;
}