/**
 * @Time : 2022/10/2-10:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个仅由小写英文字母组成的字符串 s 。在一步操作中，你可以：

删除 整个字符串 s ，或者
对于满足 1 <= i <= s.length / 2 的任意 i ，如果 s 中的 前 i 个字母和接下来的 i 个字母 相等 ，删除 前 i 个字母。
例如，如果 s = "ababc" ，那么在一步操作中，你可以删除 s 的前两个字母得到 "abc" ，因为 s 的前两个字母和接下来的两个字母都等于 "ab" 。

返回删除 s 所需的最大操作数。

 

示例 1：

输入：s = "abcabcdabc"
输出：2
解释：
- 删除前 3 个字母（"abc"），因为它们和接下来 3 个字母相等。现在，s = "abcdabc"。
- 删除全部字母。
一共用了 2 步操作，所以返回 2 。可以证明 2 是所需的最大操作数。
注意，在第二步操作中无法再次删除 "abc" ，因为 "abc" 的下一次出现并不是位于接下来的 3 个字母。
示例 2：

输入：s = "aaabaab"
输出：4
解释：
- 删除第一个字母（"a"），因为它和接下来的字母相等。现在，s = "aabaab"。
- 删除前 3 个字母（"aab"），因为它们和接下来 3 个字母相等。现在，s = "aab"。
- 删除第一个字母（"a"），因为它和接下来的字母相等。现在，s = "ab"。
- 删除全部字母。
一共用了 4 步操作，所以返回 4 。可以证明 4 是所需的最大操作数。
示例 3：

输入：s = "aaaaa"
输出：5
解释：在每一步操作中，都可以仅删除 s 的第一个字母。
 

提示：

1 <= s.length <= 4000
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-deletions-on-a-string
 */
class Solution {
public:
    /**
     * 时间复杂度n平方的记忆化搜索
     * countDelete(lo)返回删除子串s[lo, n - 1]的最多删除次数
     * 对于任意i使得s[lo, i]可以被删除，那么可能的答案就是 1 + countDelete(i + 1)
     * 难点在于找到s[lo, n - 1]上可以切割的点i
     *
     * check[i][j]表示子串s[i,j]可以被删除
     *
     * 方法1：使用lcp来预处理check
     * lcp: s[i, n - 1]与s[j, n - 1]的最长公共前缀
     * 如果lcp[i][j + 1] >= j - i + 1
     * 也就是s[i, n - 1], s[j + 1, n - 1]的最长公共前缀长度大于等于s[i,j]的长度
     * 那么根据题目s[i,j]就可以被删除check[i][j]=true
     *
     * 方法2：使用字符串hash
     */
    int n;
    vector<int> cache;
    vector<vector<bool>> check;
    int deleteString(string s) {
        n = s.size();
        cache = vector(n, 0);
        getCheck(s);
        return countDelete(0);
    }

    int countDelete(int lo){
        if(cache[lo] != 0) return cache[lo];
        int res = 1;
        for(int i = lo; i <= (lo + n - 2) / 2; i++){
            if(check[lo][i]) res = max(res, countDelete(i + 1) + 1);
        }
        cache[lo] = res;
        return res;
    }
    // 方法2
    void getCheck(string& s){

    }

    // 方法1
//    void getCheck(string& s){
//        vector<vector<int>> lcp = vector(n, vector(n, 0));
//        for(int j = n - 1; j >= 0; j--){
//            for(int i = j; i >= 0; i--){
//                if(s[i] != s[j]) continue;
//                if(i != n - 1 && j != n - 1)
//                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
//                else lcp[i][j] = 1;
//            }
//        }
//        check = vector(n, vector(n, false));
//        for(int i = 0; i < n - 1; i++){
//            for(int j = i; j <= (i + n - 2) / 2; j++)
//                check[i][j] = lcp[i][j + 1] >= j - i + 1;
//        }
//    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}