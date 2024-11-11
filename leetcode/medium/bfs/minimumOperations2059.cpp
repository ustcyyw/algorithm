/**
 * @Time : 2022/12/31-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums, int start, int goal) {
        vector<bool> marked(1001, false);
        marked[start] = true;
        queue<int> queue;
        queue.push(start);
        int step = 1;
        while (!queue.empty()){
            int sz = queue.size();
            for(int i = 0; i < sz; i++){
                int cur = queue.front();
                queue.pop();
                for(int num : nums){
                    int t1 = cur + num, t2 = cur - num, t3 = cur ^ num;
                    if(t1 == goal || t2 == goal || t3 == goal) return step;
                    add(marked, queue, t1);
                    add(marked, queue, t2);
                    add(marked, queue, t3);
                }
            }
            step++;
        }
        return -1;
    }

    void add(vector<bool>& marked, queue<int>& queue, int t){
        if(t >= 0 && t <= 1000 && !marked[t]){
            marked[t] = true;
            queue.push(t);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}