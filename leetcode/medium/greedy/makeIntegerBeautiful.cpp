/**
 * @Time : 2022/11/1-3:56 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long makeIntegerBeautiful(long long n, int target) {
        string s = to_string(n);
        vector<int> nums;
        nums.push_back(0);
        for(char c : s)
            nums.push_back(c - '0');
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum <= target) return 0;
        int m = nums.size(), i = m - 1;
        while (i >= 0 && sum + 1 > target)
            sum -= nums[i--];
        while (i >= 0 && nums[i] + 1 == 10)
            nums[i--] = 0;
        nums[i]++;
        long long res = 0;
        for(int j = 0; j <= i; j++)
            res = res * 10 + nums[j];
        res = (long long)pow(10, m - i - 1) * res;
        return res - n;
    }
};

int main(){
    Solution s;
    s.makeIntegerBeautiful(188994725, 20);
    cout << 0 << endl;
}