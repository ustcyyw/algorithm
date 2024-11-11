/**
 * @Time : 2023/9/5-10:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
//    int longestEqualSubarray(vector<int>& nums, int k) {
//        unordered_map<int, int> map;
//        multiset<int> cnt;
//        int res = 0, n = nums.size();
//        for(int l = 0, r = 0; r < n; r++) {
//            int n1 = nums[r];
//            if(map[n1] != 0) cnt.erase(cnt.find(map[n1]));
//            map[n1]++;
//            cnt.insert(map[n1]);
//            while (*(--cnt.end()) + k < r - l + 1) {
//                int n2 = nums[l++];
//                cnt.erase(cnt.find(map[n2]));
//                map[n2]--;
//                cnt.insert(map[n2]);
//            }
//            res = max(res, *(--cnt.end()));
//        }
//        return res;
//    }

    int longestEqualSubarray(vector<int>& nums, int k) {
        unordered_map<int, vector<int>> map;
        int res = 0, n = nums.size();
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            if(!map.count(num)) map[num] = {};
            map[num].push_back(i);
        }
        for(auto& pair : map) {
            vector<int>& arr = pair.second;
            for(int l = 0, r = 0; r < arr.size(); r++) {
                while (arr[r] - arr[l] > k + r - l) l++;
                res = max(res, r - l + 1);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}