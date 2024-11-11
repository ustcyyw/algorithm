/**
 * @Time : 2023/3/18-1:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        int step = 1, end = stoi(target);
        if(end == 0) return 0;
        unordered_set<int> dead;
        for(string& word : deadends)
            dead.insert(stoi(word));
        if(dead.count(0) || dead.count(end)) return -1;
        dead.insert(0);
        queue<int> queue;
        queue.push(0);
        while (!queue.empty()){
            int sz = queue.size();
            for(int i = 0; i < sz; i++){
                int num = queue.front();
                queue.pop();
                for(int k = 0, t = 1; k < 4; k++, t *= 10){
                    int digit = num % (t * 10) / t;
                    int d1 = (digit + 1) % 10, d2 = (digit + 9) % 10;
                    int n1 = num - digit * t + d1 * t, n2 = num - digit * t + d2 * t;
                    if(n1 == end || n2 == end) return step;
                    add(dead, queue, n1), add(dead, queue, n2);
                }
            }
            step++;
        }
        return -1;
    }

    void add(unordered_set<int>& dead, queue<int>& queue, int num){
        if(dead.count(num)) return;
        dead.insert(num);
        queue.push(num);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}