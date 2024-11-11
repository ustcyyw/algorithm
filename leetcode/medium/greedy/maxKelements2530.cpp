/**
 * @Time : 2023/1/10-9:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> pq;
        for(int num : nums) pq.push(num);
        long long res = 0ll;
        while (k-- > 0){
            int num = pq.top();
            pq.pop();
            res += num;
            pq.push(num % 3 == 0 ? num / 3 : num / 3 + 1);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}