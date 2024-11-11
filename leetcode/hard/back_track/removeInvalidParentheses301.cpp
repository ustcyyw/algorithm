/**
 * @Time : 2023/3/22-12:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, len = 0;
    string s;
    unordered_set<string> set;
    vector<string> removeInvalidParentheses(string s) {
        this->s = s;
        n = s.size();
        backTrack(0, 0, 0);
        vector<string> res;
        for(auto& str : set)
            res.push_back(str);
        return res;
    }

    void backTrack(int cur, int status, int left){
        if(cur == n){
            if(left > 0) return;
            int temp = bit_count(status);
            if(temp > len){
                len = temp;
                set.clear();
            }
            if(temp == len) set.insert(format(status));
            return;
        }
        if(left > n - cur) return; // 即便后面全部选右括号，也抵消不了左括号了
        char c = s[cur];
        int ns = status | (1 << cur); // 要选取当前字符，需要更改状态
        if(c != '(' && c != ')') backTrack(cur + 1, ns, left);
        else {
            backTrack(cur + 1, status, left); // 不选当前字符
            if(c == '(') backTrack(cur + 1, ns, left + 1); // 是左括号，并选取
            else if(left > 0) backTrack(cur + 1, ns, left - 1); // 是右括号
        }
    }

    string format(int status){
        string str;
        for(int i = 0; i < n; i++)
            if((1 << i) & status) str.push_back(s[i]);
        return str;
    }

    int bit_count(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        i = (i + (i >> 4)) & 0x0f0f0f0f;
        i = i + (i >> 8);
        i = i + (i >> 16);
        return i & 0x3f;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}