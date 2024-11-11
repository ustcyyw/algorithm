/**
 * @Time : 2023/2/25-1:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.size();
        vector<bool> valid(n, true);
        stack<int> stack;
        for(int i = 0; i < n; i++){
            if(s[i] == '(') stack.push(i);
            if(s[i] == ')') {
                if(stack.empty()) valid[i] = false;
                else stack.pop();
            }
        }
        while (!stack.empty()){
            valid[stack.top()] = false;
            stack.pop();
        }
        string res;
        for(int i = 0; i < n; i++)
            if(valid[i]) res.push_back(s[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}