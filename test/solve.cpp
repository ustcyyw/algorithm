#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long long a1 = abs(nums[0]), a2 = abs(nums[1]);
        int n =  nums.size();
        long long b1 = abs(nums[n - 1]), b2 = abs(nums[n - 2]);
        return max({b1 * b2, a1 * a2, b1 * a1}) * 1e5;
    }
};

int main() {
    vector<int> arr1 = {3,1};
    vector<int> arr2 = {2,3};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
}
