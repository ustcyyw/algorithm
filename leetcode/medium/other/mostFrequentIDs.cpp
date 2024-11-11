/**
 * @Time : 2024/3/24-1:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛390 t3 按题意模拟
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
class Solution {
public:
    vector<long long> mostFrequentIDs(vector<int>& nums, vector<int>& freq) {
        unordered_map<int, ll> map; // num -> 频率
        multiset<ll> set; // 频率的集合
        vector<long long> res;
        for(int i = 0; i < nums.size(); i++) {
            int num = nums[i], f = freq[i];
            if(!map.count(num)) {
                map[num] = f, set.insert(f);
            } else {
                set.erase(set.find(map[num]));
                map[num] += f;
                set.insert(map[num]);
            }
            res.push_back(*set.rbegin());
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}