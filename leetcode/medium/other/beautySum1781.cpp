/**
 * @Time : 2023/5/3-1:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int beautySum(string s) {
        int ans = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            vector<int> count(26, 0);
            for(int max_val = -1, j = i; j < n; j++){
                int c = s[j] - 'a', min_val = INT_MAX;
                count[c]++;
                for(int k = 0; k < 26; k++)
                    if(count[k]) min_val = min(count[k], min_val);
                max_val = max(count[c], max_val);
                ans += max_val - min_val;
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}