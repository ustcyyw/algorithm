/**
 * @Time : 2022/7/19-8:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& nums) {
        int res = -1;
        vector<vector<int>> pair_map = vector(100, vector(2, 0));
        for(int num : nums){
            vector<int>& pair = pair_map[digit_sum(num)];
            if(pair[1] <= num){
                pair[0] = pair[1];
                pair[1] = num;
            } else if(pair[0] < num)
                pair[0] = num;
            if(pair[0] > 0)
            res = max(res, pair[0] + pair[1]);
        }
        return res;
    }

    int digit_sum(int num){
        int temp = 10, res = 0;
        while (num != 0){
            res += num % temp;
            num /= temp;
        }
        cout << res << endl;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {368,369,307,304,384,138,90,279,35,396,114,328,251,364,300,191,438,467,183};
    s.maximumSum(arr);
    cout << 0 << endl;
}