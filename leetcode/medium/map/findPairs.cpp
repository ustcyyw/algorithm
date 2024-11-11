/**
 * @Time : 2022/6/17-2:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long base = 100000000l;
    int findPairs(vector<int>& nums, int k) {
        int count = 0;
        unordered_set<int> set, keys;
        for(int num : nums){
            if(set.find(num - k) != set.end() && keys.find(num * base + num - k) == keys.end()){
                count++;
                keys.insert(num * base + num - k);
            }
            if(set.find(num + k) != set.end() && keys.find((num + k) * base + num) == keys.end()){
                count++;
                keys.insert((num + k) * base + num);
            }
            set.insert(num);
        }
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}