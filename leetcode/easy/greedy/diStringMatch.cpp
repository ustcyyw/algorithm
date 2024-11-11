/**
 * @Time : 2022/5/9-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> diStringMatch(string s) {
        vector<int> res;
        int hi = s.size(), lo = 0;
        for(char& c : s){
            if(c == 'I') res.push_back(lo++);
            else res.push_back(hi--);
        }
        res.push_back(lo);
        return res;
    }
};

int main(){

}