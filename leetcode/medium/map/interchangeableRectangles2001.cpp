/**
 * @Time : 2022/9/2-10:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        unordered_map<string, long long> count;
        long long res = 0;
        for(auto& pair : rectangles){
            int h = pair[0], w = pair[1], t = gcd(h, w);
            string key = to_string(h / t) + "/" + to_string(w / t);
            if(count.count(key))
                res += count[key];
            count[key]++;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}