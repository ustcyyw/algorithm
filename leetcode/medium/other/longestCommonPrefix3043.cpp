/**
 * @Time : 2024/2/28-9:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> set;
        for(int num : arr1) {
            while(num > 0) {
                set.insert(num);
                num /= 10;
            }
        }
        int res = 0;
        for(int num : arr2) {
            while(num > 0) {
                if(set.count(num)) {
                    res = max(res, (int)to_string(num).size());
                    break;
                }
                num /= 10;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}