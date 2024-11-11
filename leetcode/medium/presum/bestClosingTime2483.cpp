/**
 * @Time : 2022/11/30-11:12 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.size();
        vector<int> preSum(n + 1, 0);
        for(int i = 1; i <= n; i++)
            preSum[i] = preSum[i - 1] + (customers[i - 1] == 'Y' ? 1 : 0);
        int val = INT_MAX, ans = -1;
        for(int i = 0; i <= n; i++){
            int loss = i - preSum[i] + preSum[n] - preSum[i];
            if(loss < val){
                val = loss;
                ans = i;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}