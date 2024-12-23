#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int P = 13331;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        vector<int> cnt(101, 0);
        int n = nums.size();
        for(int i = n - 1; i >= 0; i--) {
            if(++cnt[nums[i]] == 2) {
                int m = i + 1;
                return m % 3 == 0 ? m / 3 : m / 3 + 1;
            }
        }
        return 0;
    }
};

int main() {
    vector<int> arr1 = {3,8,7,8,7,5};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    s.minLength("0101", 0);
}
