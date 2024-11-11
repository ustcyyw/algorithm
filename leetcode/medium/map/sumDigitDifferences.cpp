/**
 * @Time : 2024/5/19-10:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛398 t3 hashmap计数
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        unordered_map<int, int> map[10];
        long long ans = 0;
        for(int i = 0; i < nums.size(); i++) {
            string temp = to_string(nums[i]);
            for(int j = 0; j < temp.size(); j++) {
                int c = temp[j] - 'a';
                ans += i - map[j][c];
                map[j][c]++;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}