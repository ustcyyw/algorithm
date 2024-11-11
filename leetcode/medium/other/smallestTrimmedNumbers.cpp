/**
 * @Time : 2022/7/19-8:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        int n = nums[0].size();
        vector<int> res;
        for(vector<int>& query : queries){
            res.push_back(index_of_query(nums, query[0], query[1], n));
        }
        return res;
    }

    int index_of_query(vector<string>& nums, int k, int t, int n){
        vector<pair<int, string>> arr;
        for(int i = 0; i < nums.size(); i++){
            string cur = nums[i];
            int j = n - t;
            while (cur[j] == '0') j++;
            arr.push_back(make_pair(i, cur.substr(j)));
        }
        sort(arr.begin(), arr.end(), [](pair<int, string>& a, pair<int, string>& b) -> bool {
            if(a.second.size() != b.second.size())
                return a.second.size() < b.second.size();
            if(a.second != b.second)
                return a.second < b.second;
            return a.first < b.first;
        });
        return arr[k - 1].first;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}