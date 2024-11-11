/**
 * @Time : 2024/4/14-4:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛393 t1
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string findLatestTime(string s) {
        if(s[0] == '?') {
            if(s[1] <= '1' || s[1] == '?') s[0] = '1';
            else s[0] = '0';
        }
        if(s[1] == '?') {
            if(s[0] == '1') s[1] = '1';
            else s[1] = '9';
        }
        if(s[3] == '?') s[3] = '5';
        if(s[4] == '?') s[4] = '9';
        return s;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}