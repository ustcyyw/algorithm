/**
 * @Time : 2025/1/19-3:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3430 贡献法 单调栈 数学
 */
 /*
  * 最大值最小值 一个做法 找到nums[i]为最大值的子数组的范围
  * 相同值的元素避免重复：单调栈一边取等号 一边不取即可
  * 具体计算nums[i]的贡献时
  * 枚举左边的位置 看看右边哪些位置会导致子数组长度超过k
  * 有一些左边的位置，右边所有可能的位置都可以取。
  * 从某一个临界点开始 右边的位置就不能全部取 就进入等差数列求和的部分
  */
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