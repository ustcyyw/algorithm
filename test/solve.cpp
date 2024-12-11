#include<bits/stdc++.h>

using namespace std;
const int N = 1e4, mod = 1e9 + 7;

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        set<int> st;
        for(int num : nums)
            st.insert(num);
        if(*st.begin() < k) return -1;
        return st.size() - st.count(k);
    }
};

int main() {
    vector<int> arr1 = {7,3,6,18,22,50};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
}
