/**
 * @Time : 2022/12/5-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int closestCost(vector<int>& baseCosts, vector<int>& toppingCosts, int target) {
        int n = baseCosts.size(), m = toppingCosts.size() * 2;
        vector<int> toppings;
        for(int num : toppingCosts){
            toppings.push_back(num); toppings.push_back(num);
        }
        vector<int> topSum;
        topSum.push_back(0);
        int u = (1 << m) - 1;
        for(int s = u; s ; s = (s - 1) & u){
            int sum = 0;
            for(int i = 0; i < m; i++)
                if(((1 << i) & s) > 0) sum += toppings[i];
            topSum.push_back(sum);
        }
        sort(baseCosts.begin(), baseCosts.end());
        sort(topSum.begin(), topSum.end());
        int diff = INT_MAX, res = -1;
        for(int lo = 0, hi = topSum.size() - 1; lo < n; lo++){
            int base = baseCosts[lo];
            while (hi >= 0 && topSum[hi] + base >= target) hi--;
            if(hi >= 0 && target - base - topSum[hi] <= diff){
                diff = target - base - topSum[hi];
                res = base + topSum[hi];
            }
            if(hi <  (int)topSum.size() - 1 && base + topSum[hi + 1] - target < diff){
                diff = base + topSum[hi + 1] - target;
                res = base + topSum[hi + 1];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {10}, arr2 = {1};
    s.closestCost(arr1, arr2, 1);
    cout << 0 << endl;
}