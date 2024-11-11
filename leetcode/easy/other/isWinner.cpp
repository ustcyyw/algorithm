/**
 * @Time : 2023/4/30-12:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        int p1 = get_point(player1), p2 = get_point(player2);
        if(p1 == p2) return 0;
        return p1 > p2 ? 1 : 2;
    }

    int get_point(vector<int>& nums) {
        int sum = nums[0], n = nums.size();
        if(n == 1) return sum;
        sum += nums[0] == 10 ? nums[1] * 2 : nums[1];
        for(int i = 2; i < n; i++) {
            if(nums[i - 1] == 10 || nums[i - 2] == 10) sum += nums[i] * 2;
            else sum += nums[i];
        }
        return sum;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}