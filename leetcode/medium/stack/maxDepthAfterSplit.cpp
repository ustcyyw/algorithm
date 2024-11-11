/**
 * @Time : 2022/6/22-11:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size(), depth = 0, curDepth = 0, d = 0;
        vector<int> arr = vector(n, 0);
        for(char c : seq){
            if(c == '(') {
                curDepth++;
                depth = max(depth, curDepth);
            }
            else curDepth--;
        }
        d = depth / 2, curDepth = 0;
        for(int i = 0; i < n; i++){
            char c = seq[i];
            if(c == '(' && curDepth < d) {
                curDepth++;
                arr[i] = 1;
            }
            if(c == ')' && curDepth > 0){
                curDepth--;
                arr[i] = 1;
            }
        }
        return arr;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}