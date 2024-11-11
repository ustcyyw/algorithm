/**
 * @Time : 2024/5/13-10:27 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 分为k组 因为跳跃间隔是确定的
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        vector<vector<int>> groups(k);
        for(int i = 0; i < energy.size(); i++) {
            groups[i % k].push_back(energy[i]);
        }
        int ans = INT_MIN;
        for(auto& arr : groups) {
            ans = max(ans, cal(arr));
        }
        return ans;
    }

    int cal(vector<int>& arr) {
        int m = arr.size(), sum = 0, res = INT_MIN;
        for(int i = m - 1; i >= 0; i--) {
            sum += arr[i];
            res = max(res, sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}