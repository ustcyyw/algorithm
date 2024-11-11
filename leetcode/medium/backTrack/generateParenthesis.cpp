/**
 * @Time : 2022/6/13-11:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 括号。设计一种算法，打印n对括号的所有合法的（例如，开闭一一对应）组合。

说明：解集不能包含重复的子集。

例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/bracket-lcci
 */
class Solution {
    /**
     * 执行用时：4 ms, 在所有 C++ 提交中击败了67.34%的用户
     * 内存消耗：17.4 MB, 在所有 C++ 提交中击败了5.10%的用户
     */
public:
    int n;
    vector<string> generateParenthesis(int pair) {
        this->n = pair * 2;
        vector<string> res;
        backTrack(res, string(n, ' '), pair, pair, 0);
        return res;
    }

    void backTrack(vector<string>& res, string temp, int left, int right, int cur){
        if(cur == n){
            res.push_back(string(temp));
            return;
        }
        if(left < right) {
            temp[cur] = ')';
            backTrack(res, temp, left, right - 1, cur + 1);
        }
        if(left > 0){
            temp[cur] = '(';
            backTrack(res, temp, left - 1, right, cur + 1);
        }
    }
};

int main(){

}