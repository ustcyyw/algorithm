/**
 * @Time : 2023/3/4-2:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int kSimilarity(string s1, string s2) {
        n = s1.size();
        return minSwap(s1, s2, 0);
    }

    int minSwap(string& s1, string& s2, int cur){
        if(cur == n) return 0;
        if(s1[cur] == s2[cur]) return minSwap(s1, s2, cur + 1);
        for(int i = cur + 1; i < n; i++){
            if(s1[cur] == s2[i] && s1[i] == s2[cur]){
                swap(s1[cur], s1[i]);
                int t = minSwap(s1, s2, cur + 1);
                swap(s1[cur], s1[i]);
                return t + 1;
            }
        }
        int res = INT_MAX;
        for(int i = cur + 1; i < n; i++){
            if(s1[i] == s2[cur]){
                swap(s1[cur], s1[i]);
                res = min(res, minSwap(s1, s2, cur + 1) + 1);
                swap(s1[cur], s1[i]);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}