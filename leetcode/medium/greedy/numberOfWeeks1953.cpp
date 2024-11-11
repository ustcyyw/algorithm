/**
 * @Time : 2022/12/28-3:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        long long sum = 0, maxVal = -1;
        for(int num : milestones){
            sum += num;
            maxVal = max(maxVal, (long long)num);
        }
        if(maxVal * 2 <= sum) return sum;
        return (sum - maxVal) * 2 + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}