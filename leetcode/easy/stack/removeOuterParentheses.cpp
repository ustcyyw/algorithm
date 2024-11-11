/**
 * @Time : 2022/6/2-1:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
 * 内存消耗：6.7 MB, 在所有 C++ 提交中击败了20.58%的用户
 */
class Solution {
public:
    string removeOuterParentheses(string s) {
        int n = s.size();
        vector<bool> in = vector(n, false);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(s[i] == '(') stack.push(i);
            else if(stack.size() > 1){
                in[i] = true;
                in[stack.top()] = true;
                stack.pop();
            } else stack.pop();
        }
        string res;
        for(int i = 0; i < n; i++)
            if(in[i]) res.push_back(s[i]);
        return res;
    }
};

int main(){

}