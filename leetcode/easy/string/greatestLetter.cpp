/**
 * @Time : 2022/6/19-6:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string greatestLetter(string s) {
        vector<int> upper = vector(26, 0), lower = vector(26, 0);
        for(char c : s){
            if(c <= 'Z' && c >= 'A') upper[c - 'A'] = 1;
            else lower[c - 'a'] = 1;
        }
        for(int i = 25; i >= 0; i--)
            if(upper[i] && lower[i]) return string(1, (char)(i + 'A'));
        return "";
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}