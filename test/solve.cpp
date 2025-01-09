#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 128;

class Solution {
public:
    vector<int> resultsArray(vector<vector<int>>& queries, int k) {
        multiset<int> st;
        vector<int> ans;
        int val = -1;
        for(auto& pos : queries) {
            int cur = abs(pos[0]) + abs(pos[1]);
            st.insert(cur);
            if(st.size() > k) st.erase(--st.end());
            if(st.size() == k) val = *st.rbegin();
            ans.push_back(val);
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {2,2,3,3,4,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{8,7,6},{8,3,2}};
    Solution s;
}
