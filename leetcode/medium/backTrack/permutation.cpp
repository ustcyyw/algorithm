/**
 * @Time : 2022/6/11-9:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 无重复字符串的排列组合。编写一种方法，计算某字符串的所有排列组合，字符串每个字符均不相同。

示例1:

 输入：S = "qwe"
 输出：["qwe", "qew", "wqe", "weq", "ewq", "eqw"]
示例2:

 输入：S = "ab"
 输出：["ab", "ba"]
提示:

字符都是英文字母。
字符串长度在[1, 9]之间。


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/permutation-i-lcci
 */
class Solution {
public:
    /**
     * 执行用时：24 ms, 在所有 C++ 提交中击败了50.84%的用户
     * 内存消耗：19.4 MB, 在所有 C++ 提交中击败了70.11%的用户
     */
    int n;
    vector<string> permutation(string s) {
        n = s.size();
        vector<string> res;
        backTrack(res, s, string (n, ' '), 0, (1 << n) - 1);
        return res;
    }

    void backTrack(vector<string>& res, string s, string temp, int cur, int state){
        if(state == 0) res.push_back(string(temp));
        for(int i = 0; i < n; i++){
            int mask = 1 << i;
            if(mask & state){
                temp[cur] = s[i];
                backTrack(res, s, temp, cur + 1, state ^ mask);
            }
        }
    }
};

int main(){

}