/**
 * @Time : 2023/12/26-12:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mod = 1e9 + 7;
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        format(hFences, m), format(vFences, n);
        unordered_set<int> set;
        for(int i = 0; i < hFences.size(); i++) {
            for(int j = i + 1; j < hFences.size(); j++)
                set.insert(hFences[j] - hFences[i]);
        }
        long long len = 0;
        for(int i = 0; i < vFences.size(); i++) {
            for(int j = i + 1; j < vFences.size(); j++) {
                long long t = vFences[j] - vFences[i];
                if(set.count(t)) len = max(len, t);
            }
        }
        return len == 0 ? -1 : len * len % mod;
    }

    void format(vector<int>& arr, int n) {
        arr.push_back(1), arr.push_back(n);
        sort(arr.begin(), arr.end());
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}