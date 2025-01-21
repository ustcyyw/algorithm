#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size(), ans = abs(nums[0] - nums[n - 1]);
        for(int i = 0; i < n - 1; i++)
            ans = max(ans, abs(nums[i] - nums[i + 1]));
        return ans;
    }
};

int main() {
    vector<int> arr1 = {2,2,2,1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
}
