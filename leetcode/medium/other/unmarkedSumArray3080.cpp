/**
 * @Time : 2024/3/24-3:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;

class Solution {
public:
    vector<long long> unmarkedSumArray(vector<int>& nums, vector<vector<int>>& queries) {
        ll sum = accumulate(nums.begin(), nums.end(), 0ll);
        int n = nums.size();
        vector<vector<int>> aux;
        for(int i = 0; i < n; i++)
            aux.push_back({nums[i], i});
        sort(aux.begin(), aux.end());
        vector<int> marked(n, 0);
        vector<long long> res;
        int i = 0;
        for(auto& ope : queries) {
            int idx = ope[0], k = ope[1];
            if(!marked[idx]) marked[idx] = 1, sum -= nums[idx];
            while(k > 0 && i < n) {
                if(!marked[aux[i][1]]) {
                    marked[aux[i][1]] = 1, sum -= nums[aux[i][1]];
                    k--;
                }
                i++;
            }
            res.push_back(sum);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}