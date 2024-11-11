/**
 * @Time : 2022/12/16-4:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        unordered_map<int, int> map;
        for(int num : arr)
            map[num] = map.count(num) ? map[num] + 1 : 1;
        vector<int> counts;
        for(auto& p : map)
            counts.push_back(p.second);
        sort(counts.begin(), counts.end());
        int n = counts.size(), cnt = 0;
        for(int i = 0; i < n && k >= counts[i]; i++){
            k -= counts[i];
            cnt++;
        }
        return n - cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}