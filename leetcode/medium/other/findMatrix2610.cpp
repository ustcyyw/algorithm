/**
 * @Time : 2023/4/5-9:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        unordered_map<int, int> map;
        for(int num : nums)
            map[num] = map.count(num) ? map[num] + 1 : 1;
        vector<vector<int>> res;
        while (!map.empty()){
            vector<int> temp;
            for(auto& pair : map){
                int num = pair.first;
                temp.push_back(num);
                map[num]--;
            }
            for(int num : temp)
                if(map[num] == 0) map.erase(map.find(num));
            res.push_back(temp);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}