/**
 * @Time : 2022/6/21-11:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：12 ms, 在所有 C++ 提交中击败了74.84%的用户
     * 内存消耗：19.9 MB, 在所有 C++ 提交中击败了19.19%的用户
     */
    vector<int> divingBoard(int shorter, int longer, int k) {
        vector<int> res;
        if(k == 0) return res;
        int start = shorter * k, end = longer * k, diff = longer - shorter;
        if(diff == 0) {
            res.push_back(start);
            return res;
        }
        for(int len = start; len <= end; len += diff)
            res.push_back(len);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}