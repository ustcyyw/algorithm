/**
 * @Time : 2022/10/17-1:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool sumOfNumberAndReverse(int num) {
        for(int k = 0; k <= num; k++){
            string s = to_string(k);
            reverse(s.begin(), s.end());
            if(k + stoi(s) == num) return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}