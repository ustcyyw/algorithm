/**
 * @Time : 2022/12/5-9:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumLength(string s) {
        int lo = 0, hi = s.size() - 1;
        while (lo < hi && s[lo] == s[hi]){
            char c = s[lo];
            while (lo <= hi && s[lo] == c) lo++;
            while (hi >= lo && s[hi] == c) hi--;
        }
        return lo - hi + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}