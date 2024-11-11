/**
 * @Time : 2022/11/8-5:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countHomogenous(string s) {
        s.push_back('A');
        int n = s.size(), mod = 1e9 + 7;
        long long res = 0;
        for(int i = 0, j = 0; i < n; ){
            while (j < n && s[j] == s[i]) j++;
            long t = j - i;
            res = (res + t * (t + 1) / 2) % mod;
            i = j;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}