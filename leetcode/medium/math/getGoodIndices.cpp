/**
 * @Time : 2023/12/10-3:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        vector<int> res;
        for(int i = 0; i < variables.size(); i++) {
            vector<int> info = variables[i];
            int a = info[0], b = info[1], c = info[2], m = info[3];
            long long t = quickPower(a, b, 10);
            if(quickPower(t, c, m) == target) res.push_back(i);
        }
        return res;
    }

    long long quickPower(int a, int b, int mod){
        long long res = 1, temp = a;
        while (b != 0){
            if((b & 1) == 1) res = res * temp % mod;
            temp = temp * temp % mod;
            b >>= 1;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}