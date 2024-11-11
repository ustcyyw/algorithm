/**
 * @Time : 2022/5/22-1:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 执行用时：24 ms, 在所有 C++ 提交中击败了78.80%的用户
 * 内存消耗：24.1 MB, 在所有 C++ 提交中击败了34.23%的用户
 */
class Solution {
public:
    int repeatedNTimes(vector<int>& nums) {
        unordered_set<int> set;
        for(int& num : nums){
            if(set.find(num) != set.end()) return num;
            set.insert(num);
        }
        return -1;
    }
};

int main(){

}