/**
 * @Time : 2023/5/14-12:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> circularGameLosers(int n, int k) {
        int vis[n];
        memset(vis,0,sizeof vis);
        int pos = 0, len = 1;
        while(true){
            vis[pos] ++;
            if(vis[pos] == 2) break;
            pos = (pos + k * len) % n;
            len ++;
        }

        vector<int> res;
        for(int i=0; i<n; ++i){
            if(vis[i] == 0)
                res.push_back(i + 1);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}