/**
 * @Time : 2023/11/16-11:20 PM
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
        string temp(1, '+');
        for(char c : s)
            if(c != ' ') temp.push_back(c);
        swap(s, temp);
        stack<int> s1, s2;
        int n = s.size(), cur = -1, ope = '.', next;
        for(int i = 0; i < n; ) {
            char c = s[i];
            if(c == '+' || c == '-') {
                if(cur == -1) cur = 0;
                next = parse_num(i, s);
                cur = eval(cur, c, next);
            } else if(c == '(') { // 表示要优先计算这个括号内的值 那么前置换位置的数字和操作符号要入栈中存放
                s1.push(cur), s2.push(ope);
                cur = -1, ope = '.';
                if(s[i + 1] == '+' || s[i + 1] == '-') i++;
                else cur = parse_num(i, s);
            } else { // 遇到右边括号
                int pre = s1.top(); s1.pop();
                ope = s2.top(); s2.pop();
                cur = eval(pre, ope, cur);
                i++;
            }
        }
        return cur;
    }

    int eval(int a, char ope, int b) {
        return ope == '+' ? a + b : a - b;
    }

    int parse_num(int& i, string& s) {
        int n = s.size(), j = i + 1;
        while(j < n && s[j] >= '0' && s[j] <= '9') j++;
        int num = stoi(s.substr(i + 1, j - 1 - i));
        i = j;
        return num;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}