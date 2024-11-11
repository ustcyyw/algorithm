/**
 * @Time : 2022/6/22-10:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string defangIPaddr(string address) {
        string res;
        for(char c : address){
            if(c == '.') res += "[.]";
            else res.push_back(c);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}