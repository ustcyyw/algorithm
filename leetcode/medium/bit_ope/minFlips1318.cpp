/**
 * @Time : 2022/11/26-8:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFlips(int a, int b, int c) {
        bitset<32> setA(a), setB(b), setC(c);
        int ans = 0;
        for(int i = 0; i < 32; i++){
            if((setA[i] | setB[i]) == setC[i]) continue;
            if(setC[i]) ans += 1;
            else ans += setA[i] + setB[i];
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}