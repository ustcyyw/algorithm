/**
 * @Time : 2023/3/29-10:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& first, vector<vector<int>>& second) {
        vector<vector<int>> res;
        int n = first.size(), m = second.size();
        for(int i = 0, j = 0; i < n && j < m; ){
            int l1 = first[i][0], r1 = first[i][1], l2 = second[j][0], r2 = second[j][1];
            if(l1 <= l2) {
                if(r1 >= l2) res.push_back({l2, min(r1, r2)});
            } else {
                if(r2 >= l1) res.push_back({l1, min(r1, r2)});
            }
            if(r1 > r2) j++;
            else i++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}