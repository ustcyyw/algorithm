/**
 * @Time : 2023/9/6-3:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 选了1 不能选target-1
     * 选了2 不能选target-2
     */

    int minimumPossibleSum(int n, int target) {
        long long t = min(n, target / 2), temp = t * (t + 1) / 2;
        if(t >= n) return temp % mod;
        long long m = n - t;
        return (m * (2 * target + m - 1) / 2 + temp) % mod;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}