/**
 * @Time : 2022/6/1-11:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string printBin(double num) {
        string res = "0.";
        while (res.size() <= 32 && num > 0){
            num = num * 2;
            if(num >= 1) {
                res.push_back('1');
                num -= 1;
            } else res.push_back('0');
        }
        return res.size() > 32 ? "ERROR" : res;
    }
};

int main(){

}