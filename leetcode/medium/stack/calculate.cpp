/**
 * @Time : 2022/6/23-11:37 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        if(s[0] != '-') s = "+" + s;
        stack<int> stack;
        for(int i = 0 ; i < s.size(); ){
            int num = 0, j = i + 1;
            while (j < s.size() && isdigit(s[j]))
                num = num * 10 + (s[j++] - '0');
            if(s[i] == '-') num = -1 * num;
            if(s[i] == '/' || s[i] == '*'){
                int other = stack.top();
                stack.pop();
                int res = s[i] == '/' ? other / num : other * num;
                stack.push(res);
            } else stack.push(num);
            i = j;
        }
        int res = 0;
        while (!stack.empty()){
            res += stack.top();
            stack.pop();
        }
        return res;
    }
};

int main(){
    Solution s;
    s.calculate("3+2*2");
    cout << 0 << endl;
}