/**
 * @Time : 2023/2/11-3:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int concatenatedBinary(int n) {
        long res = 0, mod = 1e9 + 7;
        for(int i = 1, j = 1; i <= n; i++){
            if((1 << j) & i) j++;
            res = ((res << j) + i) % mod;
        }
        return (int)res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}