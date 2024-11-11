/**
 * @Time : 2023/4/6-8:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size(), ans = 0;
        vector<int> aux;
        for(int i = 0; i < n; i++){
            ans += reward1[i];
            aux.push_back(reward2[i] - reward1[i]);
        }
        sort(aux.begin(), aux.end());
        for(int i = n - 1; i >= k; i--)
            ans += aux[i];
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}