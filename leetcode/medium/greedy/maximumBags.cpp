/**
 * @Time : 2022/7/18-5:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) {
        int res = 0;
        priority_queue<int, vector<int>, greater<>> pq;
        for(int i = 0; i < capacity.size(); i++){
            int c = capacity[i], r = rocks[i];
            if(r == c) res++;
            else pq.push(c - r);
        }
        while (!pq.empty() && additionalRocks - pq.top() >= 0){
            additionalRocks -= pq.top();
            pq.pop();
            res++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}