/**
 * @Time : 2022/8/24-9:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        int max_val = 1e5;
        vector<int> count(max_val + 1, 0);
        long long preSum = 0, sum = 0, res = 1e10 + 1;
        for(int num : beans){
            count[num]++;
            sum += num;
        }
        for(int i = 0, num = 0, n = beans.size(); i <= max_val; i++){
            //sum - preSum - (n - num) * i + preSum = sum - (n - num) * i
            long long temp = sum - (long long)(n - num) * i;
            res = min(res, temp);
            num += count[i];
            preSum += (long long)count[i] * i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}