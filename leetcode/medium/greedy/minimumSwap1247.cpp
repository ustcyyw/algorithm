/**
 * @Time : 2023/2/25-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int xy = 0, yx = 0, n = s1.size();
        for(int i = 0; i < n; i++){
            if(s1[i] == s2[i]) continue;
            if(s1[i] == 'x' && s2[i] == 'y') xy++;
            else yx++;
        }
        if(xy % 2 != yx % 2) return -1;
        return xy / 2 + yx / 2 + xy % 2 * 2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}