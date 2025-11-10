#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int sortPermutation(vector<int>& nums) {
        int num = -1;
        for(int i = 0; i < nums.size(); i++) {
            if(i == nums[i]) continue;
            if(num == -1) num = nums[i];
            else num &= nums[i];
        }
        return num == -1 ? 0 : num;
    }
};

int main() {
    vector<int> arr1 = {-1,9,0,8,-5,6,-24};
    vector<int> arr2 = {2,3};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
}
