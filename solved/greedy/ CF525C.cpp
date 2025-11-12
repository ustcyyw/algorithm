/**
 * @Time : 2023/11/30-12:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 贪心 越大的边应该凑在一块
 */
#include<bits/stdc++.h>
using namespace std;

int n, num;

long long solve(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    function<int(int)> find_pair = [&](int i) -> int {
        while(i > 0 && nums[i] - nums[i - 1] > 1)
            i--;
        return i;
    };
    long long res = 0;
    for(int i = n - 1; i > 0; ) {
        int j = find_pair(i), k = j >= 3 ? find_pair(j - 2) : -1;
        if(k >= 1) res += (long long)nums[j - 1] * nums[k - 1];
        i = k - 2;
    }
    return res;
}

int main() {
    cin >> n;
    vector<int> nums;
    for(int i = 1; i <= n; i++) {
        cin >> num;
        nums.push_back(num);
    }
    cout << solve(nums) << endl;
    return 0;
}