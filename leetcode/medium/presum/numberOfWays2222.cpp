/**
 * @Time : 2023/3/2-10:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numberOfWays(string s) {
        int n = s.size();
        vector<int> zeroSum(n, 0), oneSum(n, 0);
        if(s[0] == '0') zeroSum[0] = 1;
        else oneSum[0] = 1;
        for(int i = 1; i < n; i++){
            zeroSum[i] = zeroSum[i - 1] + (s[i] == '0');
            oneSum[i] = oneSum[i - 1] + (s[i] == '1');
        }
        long long res = 0, one = s[n - 1] == '1', zero = !one;
        for(int i = n - 2; i >= 1; i--){
            if(s[i] == '0') {
                res += one * oneSum[i - 1];
                zero++;
            } else {
                res += zero * zeroSum[i - 1];
                one++;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}