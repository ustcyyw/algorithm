/**
 * @Time : 2022/6/28-12:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countAsterisks(string s) {
        int res = 0;
        s.push_back('|');
        for(int i = 0, order = 0, sum = 0; i < s.size(); i++){
            if(s[i] == '*') sum++;
            if(s[i] == '|'){
                if(order % 2 == 0) res += sum;
                sum = 0;
                order++;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}