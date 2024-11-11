/**
 * @Time : 2023/4/23-8:51 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> supplyWagon(vector<int>& supplies) {
        int n = supplies.size();
        while (supplies.size() > n / 2)
            merge(supplies);
        return supplies;
    }

    void merge(vector<int>& nums){
        int val = INT_MAX, index = -1;
        for(int i = 0; i < nums.size() - 1; i++){
            int temp = nums[i] + nums[i + 1];
            if(temp < val) {
                val = temp;
                index = i;
            }
        }
        vector<int> aux;
        for(int i = 0; i < nums.size(); i++){
            if(i == index) aux.push_back(val);
            if(i != index && i != index + 1)
                aux.push_back(nums[i]);
        }
        swap(aux, nums);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}