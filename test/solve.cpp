#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int n, k;
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        this->k = k, this->n = nums.size();
        ll ans = cal(nums);
        for(int i = 0; i < n; i++)
            nums[i] = -nums[i];
        return ans - cal(nums);
    }

    ll cal(vector<int>& nums) {
        vector<int> next = get_next(nums), pre = get_pre(nums);
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            int lb = pre[i], rb = next[i];
            ll left = i - lb + 1, right = rb - i + 1;
            ll total = left * right;
            if(rb - lb + 1 > k) {
                ll reduce = 0;
                int j = i - k;
                if(j >= lb) reduce = right * (j - lb + 1);
                int j1 = max(j + 1, lb), a1 = rb - j1 - k + 1;
                int j2 = min(i, rb - k), am = rb - j2 - k + 1;
                if(j2 >= j1) {
                    ll temp = (ll)(j2 - j1 + 1) * (a1 + am) / 2;
                    reduce += temp;
                }
                total -= reduce;
            }
            ans += total * nums[i];
        }
        return ans;
    }

    vector<int> get_next(vector<int>& nums) {
        stack<int> stack;
        vector<int> arr(n);
        for(int i = n - 1; i >= 0; i--) {
            while(!stack.empty() && nums[stack.top()] <= nums[i])
                stack.pop();
            arr[i] = stack.empty() ? n - 1 : stack.top() - 1;
            stack.push(i);
        }
        return arr;
    }

    vector<int> get_pre(vector<int>& nums) {
        stack<int> stack;
        vector<int> arr(n);
        for(int i = 0; i < n; i++) {
            while(!stack.empty() && nums[stack.top()] < nums[i])
                stack.pop();
            arr[i] = stack.empty() ? 0 : stack.top() + 1;
            stack.push(i);
        }
        return arr;
    }
};

int main() {
    vector<int> arr1 = {1,2,3};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,3},{1,2},{1,4},{2,3},{2,5},{4,5},{4,7},{5,6},{6,7}};
    Solution s;
    s.minMaxSubarraySum(arr1, 2);
}
