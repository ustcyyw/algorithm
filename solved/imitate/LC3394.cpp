/**
 * @Time : 2024/12/23-9:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3394 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool checkValidCuts(int n, vector<vector<int>>& arr) {
        vector<vector<int>> xl, yl, xr, yr;
        for(int i = 0; i < arr.size(); i++) {
            vector<int> rec = arr[i];
            xl.push_back({rec[0], i}), xr.push_back({rec[2], i});
            yl.push_back({rec[1], i}), yr.push_back({rec[3], i});
        }
        return check(xl, xr) || check(yl, yr);
    }

    bool check(vector<vector<int>>& left, vector<vector<int>>& right) {
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        unordered_set<int> st;
        int cnt = 0, n = right.size();
        for(int i = 0, j = 0; j < n; ) {
            int r = right[j][0];
            while(i < n && left[i][0] < r)
                st.insert(left[i++][1]);
            while(j < n && right[j][0] == r)
                st.erase(right[j++][1]);
            if(st.empty()) cnt++;
            if(cnt >= 3) return true;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}