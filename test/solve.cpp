#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, M = 31, N = 1e5 + 5;

class Solution {
public:
    int n;
    int longestBalanced(vector<int>& nums) {
        n = nums.size();
        int lo = 0, hi = n / 2, ans = 0;
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1, temp = check(nums, mid);
            if(temp != -1)
                lo = mid, ans = max(ans, temp);
            else hi = mid - 1;
        }
        return ans;
    }

    int check(vector<int>& nums, int c) {
        int len = -1;
        unordered_map<int, int> s0, s1;
        for(int lo = 0, hi = 0; ; ) {
            if(hi < n && (s0.size() < c || s1.size() < c || (s0.size() == c && s1.size() == c))) {
                if(s0.size() == c && s1.size() == c) len = max(len, hi - lo);
                if(nums[hi] % 2 == 0) s0[nums[hi]]++;
                else s1[nums[hi]]++;
                hi++;
            } else if(s0.size() > c || s1.size() > c) {
                if(nums[lo] % 2 == 0) {
                    s0[nums[lo]]--;
                    if(s0[nums[lo]] == 0) s0.erase(nums[lo]);
                }
                else {
                    s1[nums[lo]]--;
                    if(s1[nums[lo]] == 0) s1.erase(nums[lo]);
                }
                lo++;
            } else break;
            if(s0.size() == c && s1.size() == c) len = max(len, hi - lo);
        }
        return len;
    }
};

int main() {
    vector<int> arr1 = {14,8,9,10,13,5,15,15,1,14,3,15,2,2,15};
    vector<int> arr3 = {42,24,35};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
    s.longestBalanced(arr3);
}
